// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include "form_cfg.h"

void nana::runner::form_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    string div = make_div();
    NAR_LOG_VAR(div);

    form& f = dynamic_cast<form&>(_w);
    f.div(div.data());

    for (auto& i : widgets_())
    {
        f[i.first.str().data()] << *get_widget_(i.first);
    }

    f.collocate();
}
