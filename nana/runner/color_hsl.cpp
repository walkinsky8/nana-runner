// Created by walkinsky(lyh6188@hotmail.com), 2018/12/01
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_hsl.h"

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

    std::ostream& operator<<(std::ostream& _os, const color_hsl& _v)
    {
        _os << "hsl(" << int(_v.h() + 0.5);
        _os << ", " << int((_v.s() + 0.005) * 100) << "%";
        _os << ", " << int((_v.l() + 0.005) * 100) << "%";
        _os << ")";
        return _os;
    }
    
    void operator>>(string& _is, color_hsl& _v)
    {
        nana::color c{ _is };
        _v = c;
    }

}//end namespace runa

#endif

