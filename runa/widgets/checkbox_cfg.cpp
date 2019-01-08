// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
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

void runa::radio_group_init(nana::radio_group& _group, std::vector<nana::checkbox*> _radios)
{
    int selected = 0;
    for (int i = 0; i < _radios.size(); ++i)
    {
        if (_radios[i]->checked())
            selected = i;
        _group.add(*_radios[i]);
    }
    _radios[selected]->check(true);
}

#endif

