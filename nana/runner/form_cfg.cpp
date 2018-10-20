// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include "form_cfg.h"

#include <nana/runner/view_base.h>

#include <nana/gui/screen.hpp>

nana::appearance nana::runner::form_base_cfg::get_appearance() const
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

void nana::runner::form_base_cfg::init_widget(widget& _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    string div = make_div();
    NAR_LOG_VAR(div);

    auto& w = dynamic_cast<form_base&>(*_root_view->self_wnd_());
    w.div(div.data());

    for (auto& i : _root_view->widgets_())
    {
        if (i.second)
        {
            NAR_LOG_VAR(i.first);
            w[i.first.str().data()] << *i.second;
        }
    }

    w.collocate();
}

nana::runner::point nana::runner::form_base_cfg::get_pos() const
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

nana::runner::wnd_ptr nana::runner::form_cfg::create_wnd(window p, bool v) const
{
    return std::make_shared<ui_type>(p, API::make_center(300, 200), get_appearance());
}

nana::runner::wnd_ptr nana::runner::nested_form_cfg::create_wnd(window p, bool v) const
{
    return std::make_shared<ui_type>(p, API::make_center(300, 200), get_appearance());
}

