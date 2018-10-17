// Created by walkinsky(lyh6188@hotmail.com), 2018/10/17
#include "stdafx.h"

#include "spinbox_cfg.h"

void nana::runner::spinbox_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!editable_().empty())
        w.editable(editable_().value());
    
    int b{ 0 }, l{ 100 }, s{ 1 };
    if (!begin_().empty())
        b = begin_().value();
    if (!last_().empty())
        l = last_().value();
    if (!step_().empty())
        s = step_().value();
    w.range(b, l, s);

    if (!value_().empty())
        w.value(value_());

    if (!prefix_().empty() || !suffix_().empty())
        w.modifier(prefix_(), suffix_());
}

