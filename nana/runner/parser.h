// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/istr.h>
#include <nana/runner/node.h>

namespace nana::runner
{
    class parser
    {
        node node_;

    public:
        void do_parse(string _s);

    };

}
