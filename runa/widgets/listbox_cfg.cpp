/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/listbox_cfg.h>

#include <runa/widgets/option_cfg.h>

#include <runa/foundation/app_base.h>

void runa::listbox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!sortable_().empty())
        w.sortable(sortable_().value());

    if (!show_header_().empty())
        w.show_header(show_header_().value());

    for (auto& i : headers_())
    {
        auto& h = i->cast<option_cfg>();
        if (h.width_().empty())
            w.append_header(h.get_caption());
        else
            w.append_header(h.get_caption(), h.width_().value());
    }

    for (auto& i : categories_())
    {
        auto& cfg = i->cast<option_cfg>();
        auto cat = w.append(cfg.get_caption());
        for (auto& item : cfg.children_())
        {
            cat->append(item->get_caption());
        }
    }
}

#endif

