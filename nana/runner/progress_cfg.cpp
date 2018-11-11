// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "progress_cfg.h"

void nana::runner::progress_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);
    w.amount((unsigned)amount_());
    w.value((unsigned)value_());
    w.unknown(unknown_());
}

#endif

