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

runa::font_model::font_model(const font& _f)
{
    name_() = _f.name();
    size_() = _f.size();
    bold_() = _f.bold();
    italic_() = _f.italic();
    strikeout_() = _f.strikeout();
    underline_() = _f.underline();
}

runa::font_model::operator runa::font() const
{
    return make_font(name_(), size_(), bold_(), italic_(), underline_(), strikeout_());
}

#endif

