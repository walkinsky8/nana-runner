// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "listbox_cfg.h"

#include <nana/runner/app_base.h>

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
        auto& cat = w.append(cfg.get_caption());
        for (auto& item : cfg.children_())
        {
            cat->append(item->get_caption());
        }
    }
}

#endif

