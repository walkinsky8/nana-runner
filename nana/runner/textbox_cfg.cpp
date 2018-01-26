// Created by walkinsky(lyh6188@hotmail.com), 2018/01/12
#include "stdafx.h"

#include "textbox_cfg.h"

void nana::runner::textbox_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!line_wrapped_().empty())
        w.line_wrapped(line_wrapped_().value());

    if (!multi_lines_().empty())
        w.multi_lines(multi_lines_().value());

    if (!editable_().empty())
        w.editable(editable_().value());

    if (!mask_().empty())
        w.mask(mask_().value());
}
