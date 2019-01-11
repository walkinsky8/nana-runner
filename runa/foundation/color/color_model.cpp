/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/11
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_model.h>

runa::color_model::color_model(const string& _v)
{
    value_() << _v;
}

runa::color_model::color_model(const color& _v)
{
    value_() << _v;
}

runa::string runa::color_model::to_string() const
{
    return value_();
}

runa::color runa::color_model::to_color() const
{
    return get_color(value_());
}

#endif

