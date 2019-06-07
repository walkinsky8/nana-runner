/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/11/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/button_cfg.h>

#include <runa/foundation/app_base.h>

void runa::button_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!icon_().empty())
    {
        w.icon(app::create_image(icon_()));
    }

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!enable_pushed_().empty())
        w.enable_pushed(enable_pushed_().value());

    if (!pushed_().empty())
        w.pushed(pushed_().value());

    if (!omitted_().empty())
        w.omitted(omitted_().value());

    if (!enable_focus_color_().empty())
        w.enable_focus_color(enable_focus_color_().value());
    
    if (!transparent_().empty())
        w.transparent(transparent_().value());

    if (!edge_effects_().empty())
        w.edge_effects(edge_effects_().value());

    if (!_click_().empty())
    {
        if (_click_() == "quit")
            w.events().click(app::quit);
        else if (_click_() == "close")
            w.events().click([_root_view] {_root_view->close(); });
        else
        {
            w.events().click([&] {app::create_view(_click_()); });
        }
    }
}

#endif

