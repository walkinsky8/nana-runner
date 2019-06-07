/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/12/01
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_hsv.h>

namespace runa
{
    color_hsv::color_hsv(nana::color const& c)
    {
        const double r = c.r() / 255.0;
        const double g = c.g() / 255.0;
        const double b = c.b() / 255.0;
        const double maxV = max_(r, g, b);
        const double minV = min_(r, g, b);
        const double diff_max_min = maxV - minV;

        if (diff_max_min == 0.0)
            h_ = 0.0;
        else if (maxV == r)
        {
            h_ = 60.0*(g - b) / diff_max_min;
            if (h_ < 0)
                h_ += 360.0;
        }
        else if (maxV == g)
            h_ = 60.0*(b - r) / diff_max_min + 120.0;
        else if (maxV == b)
            h_ = 60.0*(r - g) / diff_max_min + 240.0;
        else
        {
            assert(false);
        }

        if (maxV==0)
            s_ = 0.0;
        else
            s_ = diff_max_min / maxV;

        v_ = maxV;
    }
    
    color_hsv::color_hsv(const string& _s)
    {
        *this = get_color(_s);
    }

    nana::color color_hsv::to_color() const
    {
        const int h_i = static_cast<int>(h_ / 60);
        const double f = h_ / 60 - h_i;
        const double p = v_ * (1 - s_);
        const double q = v_ * (1 - f * s_);
        const double t = v_ * (1 - (1 - f)*s_);
        switch (h_i)
        {
        case 0:
            return make_rgb(v_, t, p);
        case 1:
            return make_rgb(q, v_, p);
        case 2:
            return make_rgb(p, v_, t);
        case 3:
            return make_rgb(p, q, v_);
        case 4:
            return make_rgb(t, p, v_);
        case 5:
            return make_rgb(v_, p, q);
        }
        return {};
    }

    string color_hsv::str() const
    {
        std::ostringstream oss;
        oss << "hsv(" << int(h() + 0.5);
        oss << "," << int((s() + 0.005) * 100) << "%";
        oss << "," << int((v() + 0.005) * 100) << "%";
        oss << ")";
        return oss.str();
    }

}//end namespace runa

#endif //__NANA_RUNNER_LIB_ALL_IN_ONE

