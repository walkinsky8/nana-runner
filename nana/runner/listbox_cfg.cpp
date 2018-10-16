// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#include "stdafx.h"

#include "listbox_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::listbox_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!sortable_().empty())
        w.sortable(sortable_().value());

    if (!show_header_().empty())
        w.show_header(show_header_().value());

    for (auto& i : headers_())
    {
        auto& h = i->cast<option_cfg>();
        w.append_header(h.caption_(), h.width_());
    }

    for (auto& i : categories_())
    {
        auto& cfg = i->cast<option_cfg>();
        auto& cat = w.append(cfg.caption_());
        for (auto& item : cfg.children_())
        {
            cat->append(item->caption_());
        }
    }
}

