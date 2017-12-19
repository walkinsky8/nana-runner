// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/view_base.h>

nana::color nana::runner::get_color(const string& _s)
{
    nana::colors* clr = enum_<nana::colors, nana::colors::black>::find_value(_s);
    if (clr)
        return color{ *clr };
    return color{ _s };
}

