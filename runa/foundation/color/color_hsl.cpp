/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/12/01
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_hsl.h>

namespace runa
{
    color_hsl::color_hsl(nana::color const& c)
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

        l_ = (maxV + minV) / 2.0;

        if (l_ == 0.0 || maxV == minV)
            s_ = 0.0;
        else if (l_ <= 0.5)
            s_ = diff_max_min / 2.0 / l_;
        else if (l_ > 0.5)
            s_ = diff_max_min / 2.0 / (1.0 - l_);
        else
        {
            assert(false);
        }
    }

    color_hsl::color_hsl(const string& s)
    {
        *this = get_color(s);
    }

    string color_hsl::str() const
    {
        std::ostringstream oss;
        oss << "hsl(" << int(h() + 0.5);
        oss << ", " << int((s() + 0.005) * 100) << "%";
        oss << ", " << int((l() + 0.005) * 100) << "%";
        oss << ")";
        return oss.str();
    }

}//end namespace runa

#endif

