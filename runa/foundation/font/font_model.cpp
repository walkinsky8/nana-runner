/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/font/font_model.h>

runa::font_model::font_model()
{
}

runa::font_model::font_model(const font& _v)
{
    name_() = _v.name();
    size_() = _v.size();
    bold_() = _v.bold();
    italic_() = _v.italic();
    strikeout_() = _v.strikeout();
    underline_() = _v.underline();
}

runa::font_model::font_model(const string& _v)
{
    font f;
    _v >> f;
    *this = self{ f };
}

runa::font runa::font_model::to_font() const
{
    return make_font(name_(), size_(), bold_(), italic_(), underline_(), strikeout_());
}

runa::string runa::font_model::to_string() const
{
    string s;
    s << to_font();
    return s;
}

#endif

