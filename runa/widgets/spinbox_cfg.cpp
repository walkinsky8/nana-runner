/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/17
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/spinbox_cfg.h>

void runa::spinbox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

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

#endif

