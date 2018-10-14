// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#include "stdafx.h"

#include "group_cfg.h"

void nana::runner::group_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!caption_align_().empty())
        w.caption_align(caption_align_().value().value());
    if (!radio_mode_().empty())
        w.radio_mode(radio_mode_().value());
    if (!enable_format_caption_().empty())
        w.enable_format_caption(enable_format_caption_().value());

    for (auto& i : children_())
    {
        if (i)
        {
            w.add_option(i->caption_());
        }
    }
}

