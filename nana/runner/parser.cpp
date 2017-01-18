// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/parser.h>
#include <nana/runner/istr.h>
#include <nana/runner/node.h>
#include <nana/runner/dumper.h>

namespace nana::runner::detail {

    enum class token
    {
        type, // @type
        begin, // {
        end, // }
        name,
        assign,
        value,
        eof
    };

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

            p_.read_the(is_blank);
            if (!p_)
                return token::eof;

            if (*p_ == tag::type)
            {
                ++p_;
                p_.read_not(is_blank) >> value_;
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

        }
    };

}

