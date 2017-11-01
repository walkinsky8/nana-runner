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

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const parser& _v)
    {
        return _v.dump(_os);
    }

}
