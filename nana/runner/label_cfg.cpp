// Created by walkinsky(lyh6188@hotmail.com), 2018/01/12
#include "stdafx.h"

#include "label_cfg.h"

void nana::runner::label_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!transparent_().empty())
        w.transparent(transparent_().value());

    if (!align_().empty() && !align_v_().empty())
        w.text_align(align_().value().value(), align_v_().value().value());
    else if (!align_().empty())
        w.text_align(align_().value().value());
    else if (!align_v_().empty())
        w.text_align(nana::align::left, align_v_().value().value());

}
