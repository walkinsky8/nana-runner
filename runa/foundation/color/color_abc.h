/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/01/03
#pragma once

#include <runa/foundation/widget_base.h>

namespace runa
{
    class color_abc
    {
        using self = color_abc;

        double a_{0.0}; // 0..1
        double b_{0.0}; // 0..1
        double c_{0.0}; // 0..1

    public:
        color_abc()
        {}
        color_abc(double _a, double _b, double _c)
            : a_{ _a }, b_{ _b }, c_{ _c }
        {}

        double a() const
        {
            return a_;
        }
        double& a()
        {
            return a_;
        }
        self& a(double _a)
        {
            a_ = _a;
            return *this;
        }

        double b() const
        {
            return b_;
        }
        double& b()
        {
            return b_;
        }
        self& b(double _b)
        {
            b_ = _b;
            return *this;
        }

        double c() const
        {
            return c_;
        }
        double& c()
        {
            return c_;
        }
        self& c(double _c)
        {
            c_ = _c;
            return *this;
        }

        bool operator!=(const self& _v) const
        {
            return a_ != _v.a_ || b_ != _v.b_ || c_ != _v.c_;
        }
        bool operator==(const self& _v) const
        {
            return !operator!=(_v);
        }

    };

}//end namespace runa

