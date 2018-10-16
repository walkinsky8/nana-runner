// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#include "stdafx.h"

#include "menubar_cfg.h"

#include "option_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::menubar_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    for (auto& i : children_())
    {
        auto& menucfg = i->cast<menu_cfg>();
        auto& m = w.push_back(menucfg.caption_());
        menucfg.init_menu(m);
    }
}

