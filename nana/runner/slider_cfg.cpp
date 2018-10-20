// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#include "stdafx.h"

#include "slider_cfg.h"

void nana::runner::slider_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!vertical_().empty())
        w.vertical(vertical_().value());

    if (!maximum_().empty())
        w.maximum(maximum_().value());

    if (!value_().empty())
        w.value(value_().value());

    if (!transparent_().empty())
        w.transparent(transparent_().value());
}
