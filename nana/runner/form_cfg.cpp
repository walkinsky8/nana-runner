// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include "form_cfg.h"

#include <nana/gui/screen.hpp>

void nana::runner::form_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    string div = make_div();
    NAR_LOG_VAR(div);

    auto& w = dynamic_cast<ui_type&>(_w);
    w.div(div.data());

    //for (auto& i : widgets_())
    //{
    //    w[i.first.str().data()] << *get_widget(i.first);
    //}

    w.collocate();
}

nana::runner::point nana::runner::form_cfg::get_pos() const
{
    auto screen = nana::screen::primary_monitor_size();
    point pt = pos_().value();
    if (!align_().empty())
    {
        switch (align_().value().value())
        {
            case nana::align::center:
                pt.x += screen.width / 2;
                break;
            case nana::align::right:
                pt.x += screen.width;
                break;
        }
    }
    if (!align_v_().empty())
    {
        switch (align_v_().value().value())
        {
        case nana::align_v::center:
            pt.y += screen.height / 2;
            break;
        case nana::align_v::bottom:
            pt.y += screen.height;
            break;
        }
    }
    return pt;
}
