// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "scroll_cfg.h"

void nana::runner::hscroll_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);
    w.amount(amount_());
    w.range(range_());
    w.value(value_());
    w.step(step_());
}

void nana::runner::vscroll_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);
    w.amount(amount_());
    w.range(range_());
    w.value(value_());
    w.step(step_());
}

#endif

