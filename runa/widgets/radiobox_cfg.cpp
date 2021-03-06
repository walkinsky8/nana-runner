/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/01/08
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/radiobox_cfg.h>

void runa::radiobox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!check_().empty())
        w.check(check_().value());
    if (!transparent_().empty())
        w.transparent(transparent_().value());
}

void runa::radio_group_init(nana::radio_group& _group, std::vector<nana::checkbox*> _radios)
{
    int selected = -1;
    for (size_t i = 0; i < _radios.size(); ++i)
    {
        if (_radios[i]->checked())
            selected = (int)i;
        _group.add(*_radios[i]);
    }
    if (selected != -1)
        _radios[selected]->check(true);
}

#endif

