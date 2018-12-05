// Created by walkinsky(lyh6188@hotmail.com), 2018/11/25
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/color_hsl_chooser_cfg.h>

void runa::color_hsl_chooser_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);
}

#endif

