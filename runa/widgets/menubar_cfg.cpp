// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/menubar_cfg.h>

#include <runa/widgets/menu_cfg.h>

#include <runa/foundation/app_base.h>

void runa::menubar_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    for (auto& i : children_())
    {
        auto& menucfg = i->cast<menu_cfg>();
        auto& m = w.push_back(menucfg.get_caption());
        menucfg.init_menu(m);
    }
}

#endif

