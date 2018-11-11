// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "panel_cfg.h"

void nana::runner::panel_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!transparent_().empty())
        w.transparent(transparent_().value());
}

#endif

