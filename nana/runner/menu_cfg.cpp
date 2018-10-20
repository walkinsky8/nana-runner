// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#include "stdafx.h"

#include "menu_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::menu_cfg::init_menu(menu& _m) const
{
    size_t idx = 0;
    for (auto& item : children_())
    {
        auto& mi = item->cast<menu_cfg>();
        if (mi.get_caption() == "___")
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
                string s = mi._click_();
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
