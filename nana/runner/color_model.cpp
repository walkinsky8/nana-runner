// Created by walkinsky(lyh6188@hotmail.com), 2018/11/11
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/color_model.h>

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

