// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#include "stdafx.h"

#include <nana/runner/parser.h>

#include <nana/runner/dumper.h>

namespace nana::runner::detail {

    // @type { name=value }
    enum class token
    {
        type,
        begin,
        end,
        name,
        assign,
        value,
        eof
    };

    bool is_type_begin(const char c)
    {
        return c == tag::type;
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
        return c == tag::string || c == tag::string2;
    }

    bool is_name_or_value_end0(const char c)
    {
        return c == tag::assign || c == tag::end || is_string_tag(c) || is_blank(c);
    }

    bool is_word_end(const char c)
    {
        return c == tag::type || c == tag::begin || c == tag::assign || c == tag::end || is_string_tag(c) || is_blank(c);
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
            p_.read(is_blank);
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

            if (*p_ == tag::assign)
            {
                //=前面的name为空没有意义
                if (!word)
                    throw_error("empty name");
                _node.name(word);
                ++p_;
                //name已经读取，后面就是value
                word = p_.read_until(is_word_end);
                // empty value
                if (!word && is_blank(*p_))
                    return true;
            }

            if (*p_ == tag::type)
            {
                if (word) 
                    throw_error("extra word before @: " + word);
                ++p_;
                word = p_.read_until(is_type_end); //c == tag::begin || is_blank(c)
                _node.type(word);
                word.clear();
                p_.read(is_blank);
                if (*p_ != tag::begin)
                    throw_error("no { after type");
            }

            if (*p_ != tag::begin)
            {
                if (is_string_tag(*p_))
                {
                    if (word)
                        throw_error("extra word before quote: " + word);
                    _node.value(read_string(p_));
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

        void throw_error(string msg)
        {
            throw std::invalid_argument(msg.c_str());
        }

    private:
        static istr read_string(istr& p)
        {
            assert(*p == tag::string || *p == tag::string2);
            const char ch = *p;
            ++p;
            istr beg = p;
            while (p && *p != ch)
                ++p;
            istr s{ beg, p };
            ++p;
            return s;
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

nana::runner::parser::parser(istr _s, bool _is_list)
{
    detail::parse(inner_, _s, _is_list);
}

nana::runner::parser::parser(const node* _outer)
    : outer_{_outer}
{
}

const nana::runner::node& nana::runner::parser::unit() const
{
    return outer_ ? *outer_ : inner_;
}

std::ostream& nana::runner::parser::dump(std::ostream& _os) const
{
    dumper d;
    d << unit();
    return _os << d;
}

