// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include "button_cfg.h"

void nana::runner::button_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

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
}
