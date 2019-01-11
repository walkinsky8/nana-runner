/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/combox_cfg.h>

#include <runa/widgets/option_cfg.h>

#include <runa/foundation/app_base.h>

void runa::combox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    size_t pos = 0;
    for (auto& i : children_())
    {
        if (i)
        {
            w.push_back(i->get_caption());
            auto& child = i->cast<option_cfg>();
            if (!child.image_().empty())
            {
                w.image(pos, app::create_image(child.image_()));
            }
        }
        ++pos;
    }

    if (!selected_().empty())
        w.option(selected_().value());
    if (!editable_().empty())
        w.editable(editable_().value());
}

void runa::operator<<(combox& _w, const strings& _v)
{
    for (auto& i : _v)
        _w.push_back(i);
}

void runa::operator>>(const combox& _w, strings& _v)
{
    for (size_t i = 0; i < _w.the_number_of_options(); ++i)
        _v.push_back(_w.text(i));
}

void runa::operator<<(combox& _w, const color_model& _v)
{
    nana::colors* p = runa::colors::find_value(_v.value_());
    if (p)
        _w << runa::colors{ *p };
    else
        _w << runa::colors{ nana::colors::black };
    _w << _v.value_();
}

void runa::operator>>(const combox& _w, color_model& _v)
{
    _v = _w.caption();
}

#endif

