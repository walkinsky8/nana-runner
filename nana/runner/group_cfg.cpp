// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "group_cfg.h"

#include "option_cfg.h"

void nana::runner::group_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

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
            auto& cfg = i->cast<option_cfg>();
            auto& r = w.add_option(cfg.get_caption());
            if (!cfg.check_().empty())
                r.check(cfg.check_().value());
            m_radios.push_back(&r);
        }
    }
}

#endif

