/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/12
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/picture_cfg.h>

#include <runa/foundation/app_base.h>

void runa::picture_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!align_().empty() || !align_v_().empty())
    {
        nana::align h = !align_().empty() ? align_().value().value() : nana::align::left;
        nana::align_v v = !align_v_().empty() ? align_v_().value().value() : nana::align_v::top;
        w.align(h, v);
    }

    if (!gradual_from_().empty() || !gradual_to_().empty() || !gradual_horizontal_().empty())
    {
        w.set_gradual_background(get_color(gradual_from_()), get_color(gradual_to_()), gradual_horizontal_().value());
    }

    if (!stretchable_().empty())
        w.stretchable(stretchable_().value());

    if (!transparent_().empty())
        w.transparent(transparent_().value());

    if (!image_().empty())
    {
        w.load(app::create_image(image_()));
    }
}

#endif

