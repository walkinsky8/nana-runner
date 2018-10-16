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
        if (i)
        {
            auto& cfg = i->cast<option_cfg>();
            auto& m = w.push_back(cfg.caption_());
            size_t idx = 0;
            for (auto& item : cfg.children_())
            {
                if (item->caption_() == "___")
                    m.append_splitter();
                else
                    m.append(item->caption_());
                auto& mi = item->cast<option_cfg>();
                if (!mi.file_().empty())
                {
                    m.image(idx, image{ app::find_file(mi.file_()) });
                }
                ++idx;
            }
        }
    }
}

