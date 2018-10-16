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
        if (mi.caption_() == "___")
            _m.append_splitter();
        else
        {
            typedef nana::drawerbase::menu::menu_item_type::item_proxy iproxy;
            if (mi._click_()=="quit")
                _m.append(mi.caption_(), [](iproxy&) { app::quit(); });
            else
                _m.append(mi.caption_());
        }
        if (!mi.file_().empty())
        {
            _m.image(idx, image{ app::find_file(mi.file_()) });
        }
        if (!mi.children_().empty())
        {
            menu* subm = _m.create_sub_menu(idx);
            mi.init_menu(*subm);
        }
        ++idx;
    }
}
