/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/18
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/checkbox_cfg.h>

void runa::checkbox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!check_().empty())
        w.check(check_().value());
    if (!radio_().empty())
        w.radio(radio_().value());
    if (!transparent_().empty())
        w.transparent(transparent_().value());
}

#endif

