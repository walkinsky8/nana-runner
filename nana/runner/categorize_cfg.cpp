// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#include "stdafx.h"

#include "categorize_cfg.h"

void nana::runner::categorize_cfg::init_widget(widget & _w) const
{
    auto& w = dynamic_cast<ui_type&>(_w);

    //if (!splitstr_().empty())
    //    w.splitstr(splitstr_());

    super::init_widget(_w);
}