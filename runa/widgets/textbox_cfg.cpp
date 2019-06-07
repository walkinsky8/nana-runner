/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/12
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/textbox_cfg.h>

void runa::textbox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!borderless_().empty())
        w.borderless(borderless_().value());

    if (!line_wrapped_().empty())
        w.line_wrapped(line_wrapped_().value());

    if (!multi_lines_().empty())
        w.multi_lines(multi_lines_().value());

    if (!editable_().empty())
        w.editable(editable_().value());

    if (!mask_().empty())
        w.mask(mask_().value());

    if (!align_().empty())
        w.text_align(align_().value().value());
}

#endif

