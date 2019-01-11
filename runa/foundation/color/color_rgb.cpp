/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/12/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_rgb.h>

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

