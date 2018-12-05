// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/parser.h>

#include <runa/base/dumper.h>

#include <runa/base/log.h>

namespace runa::detail {

    //TODO: comment
    //TODO: escape

    // @type{ name=value name='string' name="string" @type{} @type{} }
    // string escape: ^^ ^" ^' ^t ^r ^n
    // multiple string merge: '..'".."'..'
    // raw string: '''...'''  """..."""

    bool is_type_begin(const char c)
    {
        return c == tag::key;
    }

    bool is_type_end(const char c)
    {
        return c == tag::begin || is_blank(c);
    }

    bool is_name_end(const char c)
    {
        return c == tag::assign || is_blank(c);
    }

    bool is_value_end(const char c)
    {
        return c == tag::end || is_blank(c);
    }

    bool is_string_tag(const char c)
    {
        return is_quote_char(c);
    }

    bool is_word_end(const char c)
    {
        return c == tag::key || c == tag::begin || c == tag::assign || c == tag::end || is_string_tag(c) || is_blank(c);
    }

    class tokenizer
    {
        string content_;
        pcstr begin_;
        istr p_;

    public:
        tokenizer(string _content)
            : content_{ _content }, begin_{ content_.data() }, p_ { content_ }
        {
        }

        bool read(node& _node)
        {
            skip_blanks(p_);
            if (!p_)
                return false;
            //p_非空

            if (*p_ == tag::end)
            {
                ++p_;
                return false;
            }

            //c == tag::type || c == tag::begin || c == tag::assign || c == tag::end || is_string_tag(c) || is_blank(c)
            istr word = p_.read_until(is_word_end);

            // =后面跟着空格表示值为空.

            if (*p_ == tag::assign)
            {
                //=前面的name为空没有意义.
                if (!word)
                    NAR_THROW_ERROR(std::invalid_argument, "empty name");
                _node.name(word);
                ++p_;
                //name已经读取，后面就是value.
                word = p_.read_until(is_word_end);
                // empty value
                if (!word && is_blank(*p_))
                    return true;
            }

            if (*p_ == tag::key)
            {
                if (word) 
                    NAR_THROW_ERROR(std::invalid_argument, "extra word before @: " << word);
                ++p_;
                word = p_.read_until(is_type_end); //c == tag::begin || is_blank(c)
                _node.type(word);
                word.clear();
                skip_blanks(p_);
                if (*p_ != tag::begin)
                    NAR_THROW_ERROR(std::invalid_argument, "no { after type");
            }

            if (*p_ != tag::begin)
            {
                if (is_string_tag(*p_))
                {
                    if (word)
                        NAR_THROW_ERROR(std::invalid_argument, "extra word before quote: " << word);
                    bool simple = true;
                    istr strval = read_string(p_, &simple);
                    if (simple) 
                        _node.value(unquote_string(strval, nullptr)); // no escape, not multiple
                    else
                        _node.value(unescape_string(strval));
                    return true;
                }

                // normal simple value
                _node.value(word);
                return true;
            }

            ++p_; // ignore tag::begin
            while (p_)
            {
                node child;
                if (!read(child))
                    break;
                _node.add_child(child.name(), child);
            }

            return true;
        }

        void read_list(node& _node)
        {
            while (p_)
            {
                node child;
                if (!read(child))
                    break;
                _node.add_child(child.name(), child);
            }
        }

    private:
        static void skip_blanks(istr& _p)
        {
            _p.read(is_blank);
            if (*_p == tag::key && *(_p + 1) == tag::comment)
            {
                _p += 2;
                while (_p && (*_p != tag::comment || *(_p + 1) != tag::key))
                    ++_p;
                _p += 2;
                _p.read(is_blank);
            }
        }

        static istr read_string(istr& p, bool* _simple)
        {
            istr beg = p;
            int num = 0;
            while (pick_string(p, _simple))
            {
                ++num;
            }
            if (num > 1)
                if (_simple)
                    *_simple = false;
            return istr{ beg, p };
        }

        static istr pick_string(istr& p, bool* _simple)
        {
            if (!is_string_tag(*p))
                return {};
            const char quote = *p;
            if (quote == *(p + 1) && quote == *(p + 2))
                return pick_raw_string(p);
            istr beg = p;
            ++p;
            while (p && *p != quote)
            {
                if (*p == tag::escape)
                {
                    ++p;
                    if (_simple)
                        *_simple = false;
                }
                ++p;
            }
            ++p;
            return istr{ beg, p };
        }

        static istr pick_raw_string(istr& p)
        {
            const char quote = *p;
            istr beg = p;
            p += 3;
            while (p && (*p != quote || *(p + 1) != quote || *(p + 2) != quote))
                ++p;
            p += 3;
            return istr{ beg, p };
        }

        static istr unquote_string(istr s, bool* _raw)
        {
            const char c = s.first_char();
            if (is_string_tag(c))
            {
                bool raw = false;
                if (c == s[1] && c == s[2])
                {
                    s += 2;
                    raw = true;
                }
                ++s;
                if (s.last_char() == c)
                    s.remove_right(1);
                if (raw)
                {
                    if (s.last_char() == c)
                        s.remove_right(1);
                    if (s.last_char() == c)
                        s.remove_right(1);
                }
                if (_raw)
                    *_raw = raw;
            }
            return s;
        }

        static string unescape_string(istr _s)
        {
            if (!is_string_tag(_s.first_char()))
                return _s;
            string result;
            while (istr slice = pick_string(_s, nullptr))
            {
                unescape(result, slice);
            }
            return result;
        }

        static void unescape(string& _result, istr _s)
        {
            bool raw = false;
            istr p = unquote_string(_s, &raw);
            if (raw)
            {
                _result << p;
                return;
            }
            while (p)
            {
                if (*p != tag::escape)
                {
                    _result << *p;
                }
                else
                {
                    ++p;
                    const char c = *p;
                    if (c == tag::escape || c == tag::string || c == tag::string2)
                        _result << c;
                    else if (c == 'r')
                        _result << tag::cr;
                    else if (c == 'n')
                        _result << tag::nl;
                    else if (c == 't')
                        _result << tag::tab;
                    else
                    {
                        _result << tag::escape << c;
                    }
                }
                ++p;
            }
        }

    };

    void parse(node& _node, istr _s, bool _is_list)
    {
        tokenizer p{ _s };
        if (_is_list)
            p.read_list(_node);
        else
            p.read(_node);
    }

}

runa::parser::parser(istr _s, bool _is_list)
{
    detail::parse(inner_, _s, _is_list);
}

runa::parser::parser(const node* _outer)
    : outer_{_outer}
{
}

const runa::node& runa::parser::unit() const
{
    return outer_ ? *outer_ : inner_;
}

std::ostream& runa::parser::dump(std::ostream& _os) const
{
    dumper d;
    d << unit();
    return _os << d;
}

#endif

