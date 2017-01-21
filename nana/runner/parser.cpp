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

    bool is_type_end(char c)
    {
        return is_blank(c) || c == tag::begin;
    }

    class tokenizer
    {
        string content_;
        istr p_;
        string value_;

    public:
        tokenizer(string _content)
            : content_{ _content }, p_{ content_ }
        {}

        token read()
        {
            value_.clear();

            p_.read(is_blank);
            if (!p_)
                return token::eof;

            if (*p_ == tag::type)
            {
                ++p_;
                p_.read_until(is_type_end) >> value_;
                return token::type;
            }

            if (*p_ == tag::begin)
            {
                ++p_;
                return token::begin;
            }

            if (*p_ == tag::end)
            {
                ++p_;
                return token::end;
            }

            if (is_identifier_start(*p_))
            {
                p_.read(is_identifier_body) >> value_;
                return token::name;
            }

            if (*p_ == tag::assign)
            {
                ++p_;
                return token::assign;
            }

            if (is_quote_char(*p_))
            {
                read_string(p_) >> value_;
                return token::value;
            }

            p_.read_until(is_blank) >> value_;
            return token::value;
        }

        string& str()
        {
            return value_;
        }

        void throw_error(string msg)
        {
            throw std::invalid_argument(msg.c_str());
        }

    private:
        static istr read_string(istr& p)
        {
            char ch = *p;
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
                t = _p.read();
                if (t != token::assign)
                    _p.throw_error("no =");
                t = _p.read();
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
                t = _p.read();
            }
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
    using namespace detail;

}

