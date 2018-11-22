// Created by walkinsky(lyh6188@hotmail.com), 2018/11/11
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/color_model.h>

nana::runner::color_model::color_model(const string& _v)
{
    value_() << _v;
}

nana::runner::color_model::color_model(const color& _v)
{
    value_() << _v;
}

nana::runner::color_model::operator nana::runner::string() const
{
    return value_();
}

nana::runner::color_model::operator nana::runner::color() const
{
    return get_color(value_());
}

#endif

