// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#include "stdafx.h"

#include "combox_cfg.h"

#include "option_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::combox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    size_t pos = 0;
    for (auto& i : children_())
    {
        if (i)
        {
            w.push_back(i->caption_());
            auto& child = i->cast<option_cfg>();
            if (!child.image_().empty())
            {
                w.image(pos, app::create_image(child.image_()));
            }
        }
        ++pos;
    }

    if (!selected_().empty())
        w.option(selected_().value());
    if (!editable_().empty())
        w.editable(editable_().value());
}

