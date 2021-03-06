/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/menu_cfg.h>

#include <runa/foundation/app_base.h>

void runa::menu_cfg::init_menu(menu& _m) const
{
    size_t idx = 0;
    for (auto& item : children_())
    {
        auto& mi = item->cast<menu_cfg>();
        if (mi.get_caption().empty() || mi.get_caption() == "___")
            _m.append_splitter();
        else
        {
            typedef nana::drawerbase::menu::menu_item_type::item_proxy iproxy;
            if (mi._click_() == "quit")
                _m.append(mi.get_caption(), [](iproxy&) { app::quit(); });
            else if (mi._click_().empty())
                _m.append(mi.get_caption());
            else
            {
                auto s = mi._click_();
                _m.append(mi.get_caption(), [s](iproxy&) {
                    app::create_view(s);
                });
            }
        }
        if (!mi.image_().empty())
        {
            _m.image(idx, app::create_image(mi.image_()));
        }
        if (!mi.children_().empty())
        {
            menu* subm = _m.create_sub_menu(idx);
            mi.init_menu(*subm);
        }
        ++idx;
    }
}

#endif

