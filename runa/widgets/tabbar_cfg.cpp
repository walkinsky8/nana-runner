/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/17
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/tabbar_cfg.h>
#include <runa/widgets/tab_cfg.h>
#include <runa/widgets/form_cfg.h>

#include <runa/foundation/view_base.h>
#include <runa/foundation/app_base.h>

void runa::tabbar_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!close_fly_().empty())
        w.close_fly(close_fly_().value());
    if (!tb_add_().empty())
        w.toolbox(tabbar::kits::add, tb_add_().value());
    if (!tb_scroll_().empty())
        w.toolbox(tabbar::kits::scroll, tb_scroll_().value());
    if (!tb_list_().empty())
        w.toolbox(tabbar::kits::list, tb_list_().value());
    if (!tb_close_().empty())
        w.toolbox(tabbar::kits::close, tb_close_().value());

    id page_id = get_parent()->id_path() / page_id_();
    auto& page_fld = dynamic_cast<form_base&>(*_root_view->self_wnd_())[page_id.str().data()];

    for (size_t i = 0; i < children_().size(); ++i)
    {
        auto& child = children_()[i]->cast<tab_cfg>();
        w.push_back(child.get_caption());

        if (!child.tab_bgcolor_().empty())
            w.tab_bgcolor(i, get_color(child.tab_bgcolor_()));

        if (!child.tab_fgcolor_().empty())
            w.tab_fgcolor(i, get_color(child.tab_fgcolor_()));

        if (!child.tab_image_().empty())
            w.tab_image(i, app::create_image(child.tab_image_()));

        auto vp = view_obj::make_view(child, *_root_view->self_wnd_());
        _root_view->add_child_view(child.id_path(), vp);
        w.attach(i, *vp->self_wnd_());
        //NAR_LOG("fasten " << page_id << " = " << child.get_caption());
        page_fld.fasten(*vp->self_wnd_());
    }
}

void runa::tabbar_lite_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    id page_id = get_parent()->id_path() / page_id_();
    auto& page_fld = dynamic_cast<form_base&>(*_root_view->self_wnd_())[page_id.str().data()];

    for (size_t i = 0; i < children_().size(); ++i)
    {
        auto& child = children_()[i]->cast<tab_cfg>();
        w.push_back(child.get_caption());

        auto vp = view_obj::make_view(child, *_root_view->self_wnd_());
        _root_view->add_child_view(child.id_path(), vp);
        w.attach(i, *vp->self_wnd_());
        //NAR_LOG("fasten " << page_id << " = " << child.get_caption());
        page_fld.fasten(*vp->self_wnd_());
    }
}

#endif

