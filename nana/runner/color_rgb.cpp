// Created by walkinsky(lyh6188@hotmail.com), 2018/12/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_rgb.h"

namespace runa
{
    color_rgb::color_rgb(const string& _is)
    {
        *this = get_color(_is);
    }

    string color_rgb::str() const
    {
        std::ostringstream oss;
        oss << "rgb(" << r();
        oss << ", " << g();
        oss << ", " << b();
        oss << ")";
        return oss.str();
    }

}//end namespace runa

#endif

