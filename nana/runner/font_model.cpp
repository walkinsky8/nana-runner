// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/font_model.h>

nana::runner::font_model::font_model(const font& _f)
{
    name_() = _f.name();
    size_() = _f.size();
    bold_() = _f.bold();
    italic_() = _f.italic();
    strikeout_() = _f.strikeout();
    underline_() = _f.underline();
}

nana::runner::font_model::operator nana::runner::font() const
{
    return make_font(name_(), size_(), bold_(), italic_(), underline_(), strikeout_());
}

