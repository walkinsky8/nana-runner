// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/form_cfg.h>

#include <runa/foundation/view_base.h>

#include <nana/gui/screen.hpp>

nana::appearance runa::form_base_cfg::get_appearance() const
{
    nana::appearance a;
    a.taskbar = !taskbar_().empty() ? taskbar_().value() : true;
    a.floating = !floating_().empty() ? floating_().value() : false;
    a.no_activate = !no_activate_().empty() ? no_activate_().value() : false;
    a.minimize = !minimize_().empty() ? minimize_().value() : true;
    a.maximize = !maximize_().empty() ? maximize_().value() : true;
    a.sizable = !sizable_().empty() ? sizable_().value() : true;
    a.decoration = !decoration_().empty() ? decoration_().value() : true;
    return a;
}

void runa::form_base_cfg::init_widget(widget& _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    string div = make_div();
    NAR_LOG_VAR(div);

    //auto& w = dynamic_cast<form_base&>(*_root_view->self_wnd_());
    auto& w = dynamic_cast<ui_type&>(_w);
    w.div(div.data());

    for (auto& i : _root_view->child_widgets_())
    {
        if (i.second)
        {
            //NAR_LOG_VAR(i.first);
            w[i.first.str().data()] << *i.second;
        }
    }

    w.collocate();
}

runa::point runa::form_base_cfg::get_pos(size _sz) const
{
    if (_sz == size{})
        _sz = size{ 300, 200 };
    auto screen = nana::screen::primary_monitor_size();
    point pt = pos_().value();
    auto alignH = !align_().empty() ? align_().value() : nana::align::center;
    auto alignV = !align_v_().empty() ? align_v_().value() : nana::align_v::center;
    switch (alignH.value())
    {
        case nana::align::center:
            if (pos_().empty())
                pt.x = screen.width / 2 - _sz.width / 2;
            else
                pt.x += screen.width / 2;
            break;
        case nana::align::right:
            if (pos_().empty())
                pt.x = screen.width - _sz.width;
            else
                pt.x += screen.width;
            break;
    }
    switch (alignV.value())
    {
    case nana::align_v::center:
        if (pos_().empty())
            pt.y = screen.height / 2 - _sz.height / 2;
        else
            pt.y += screen.height / 2;
        break;
    case nana::align_v::bottom:
        if (pos_().empty())
            pt.y = screen.height - _sz.height;
        else
            pt.y += screen.height;
        break;
    }
    return pt;
}

runa::wnd_ptr runa::form_cfg::create_wnd(window p, bool v) const
{
    return std::make_shared<ui_type>(p, nana::API::make_center(300, 200), get_appearance());
}

runa::wnd_ptr runa::nested_form_cfg::create_wnd(window p, bool v) const
{
    return std::make_shared<ui_type>(p, nana::API::make_center(300, 200), get_appearance());
}

#endif

