// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
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

    bool is_name_or_value_end(const char c)
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
        istr p_;

    public:
        tokenizer(string _content)
            : content_{ _content }, p_{ content_ }
        {
        }
         
        bool read(node& _node)
        {
            p_.read(is_blank);
            if (!p_)
                return false;

            if (*p_ == tag::end)
            {
                ++p_;
                return false;
            }

            istr word = p_.read_until(is_word_end); //c == tag::type || c == tag::begin || c == tag::assign || c == tag::end || is_string_tag(c) || is_blank(c)

            if (word && *p_ == tag::assign)
            {
                _node.name(word);
                ++p_;
                word = p_.read_until(is_word_end);
                if (!word && is_blank(*p_))
                    return true;
            }

            if (*p_ == tag::type)
            {
                if (word)
                    throw_error("extra word " + word);
                ++p_;
                word = p_.read_until(is_type_end); //c == tag::begin || is_blank(c)
                _node.type(word);
                word.clear();
                p_.read(is_blank);
                if (*p_ != tag::begin)
                    throw_error("no {");
            }

            if (*p_ != tag::begin)
            {
                if (word)
                {
                    _node.value(word);
                    return true;
                }
            }

            ++p_;
            while (p_)
            {
                node child;
                if (!read(child))
                    break;
                p_.read(is_blank);
                if (!p_)
                    throw_error("no }");

                if (*p_ == tag::assign)
                {
                    child.name(word);
                    ++p_;
                    if (is_blank(*p_))
                    {
                        // null value
                        _node.add_child(child.name(), child);
                        continue;
                    }
                }
                if (is_string_tag(*p_))
                {
                    child .value(read_string(p_));
                }
                else if (*p_ == tag::type || *p_ == tag::begin)
                {
                    read(child);
                }

                _node.add_child(child.name(), child);
            }

            if (is_quote_char(*p_))
            {
                _node.value(read_string(p_));
                return false;
            }


            if (is_identifier_start(*word))
            {
                if (istr{ word }.read(is_identifier_body).size() == word.size())
                {
                    if (*p_ == tag::assign)
                        ++p_;
                    word >> value_;
                    return token::name;
                }
            }

            word >> value_;
            return token::value;
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

    void parse_node(node& _node, tokenizer& _p)
    {
        token t = _p.read();
        if (t == token::type)
        {
            _node.type(std::move(_p.str()));
            t = _p.read();
        }
        if (t != token::begin)
            _p.throw_error("no {");
        t = _p.read();
        while (t != token::eof && t != token::end)
        {
            if (t == token::name)
            {
                string name = std::move(_p.str());
                t = _p.read(false);
                if (t != token::assign)
                    _p.throw_error("no =");
                t = _p.read(false);
                if (t == token::value)
                {
                    string value = std::move(_p.str());
                    _node.add_attr(name, value);
                }
                else
                {
                    node child;
                    parse_node(child, _p);
                    _node.add_child(name, child);
                }
            }
            else
            {
                _p.throw_error("no name");
            }
            t = _p.read();
        }

    }

    void parse(node& _node, string _s)
    {
        tokenizer p{ _s };
        parse_node(_node, p);
    }

}

void nana::runner::parser::do_parse(string _s)
{
    detail::parse(node_, _s);
}

