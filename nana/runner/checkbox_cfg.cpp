// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#include "stdafx.h"

#include "checkbox_cfg.h"

void nana::runner::checkbox_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!check_().empty())
        w.check(check_().value());
    if (!radio_().empty())
        w.radio(radio_().value());
    if (!transparent_().empty())
        w.transparent(transparent_().value());
}
