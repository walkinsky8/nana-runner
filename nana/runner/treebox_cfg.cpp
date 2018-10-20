// Created by walkinsky(lyh6188@hotmail.com), 2018/10/20
#include "stdafx.h"

#include "treebox_cfg.h"

#include "option_cfg.h"

void nana::runner::treebox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!checkable_().empty())
        w.checkable(checkable_().value());

    for (auto& i : children_())
    {
        auto& c = i->cast<option_cfg>();
        auto p = w.insert(c.id_path(), c.get_caption());
        if (!c.children_().empty())
        {
            init_nodes(w, p, c);
        }
    }
}

void nana::runner::treebox_cfg::init_nodes(treebox& _w, item_proxy _p, option_cfg& _c)
{
    for (auto& i : _c.children_())
    {
        auto& c = i->cast<option_cfg>();
        auto p = _w.insert(_p, c.id_path(), c.get_caption());
        if (!c.children_().empty())
        {
            init_nodes(_w, p, c);
        }
    }
}
