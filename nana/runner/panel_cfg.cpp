// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#include "stdafx.h"

#include "panel_cfg.h"

void nana::runner::panel_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!transparent_().empty())
        w.transparent(transparent_().value());
}
