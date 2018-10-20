// Created by walkinsky(lyh6188@hotmail.com), 2018/10/19
#include "stdafx.h"

#include "tabframe_cfg.h"
#include "tab_cfg.h"
#include "tabbar_cfg.h"

#include <nana/runner/view_base.h>
#include <nana/runner/app_base.h>

void nana::runner::tabframe_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    id tb_id = get_parent()->id_path() / tabbar_id_();
    auto& tb = dynamic_cast<tabbar&>(*_root_view->get_widget(tb_id));
    auto& fld = dynamic_cast<form_base&>(*_root_view->self_wnd_())[(id_path() / "page").str().data()];

    for (size_t i = 0; i < children_().size(); ++i)
    {
        auto& child = children_()[i]->cast<tab_cfg>();

        auto vp = view_obj::make_view(child, *_root_view->self_wnd_());
        tb.attach(i, *vp->self_wnd_());
        m_views.push_back(vp);

        fld.fasten(*vp->self_wnd_());
    }
}

void nana::runner::tabframe_cfg::make_extra_div(string& _div) const
{
    _div << " <";
    _div << (id_path() / "page");
    _div << ">";
}

void nana::runner::tabframe_lite_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    id tb_id = get_parent()->id_path() / tabbar_id_();
    auto& tb = dynamic_cast<tabbar_lite&>(*_root_view->get_widget(tb_id));

    for (size_t i = 0; i < children_().size(); ++i)
    {
        auto& child = children_()[i]->cast<tab_cfg>();

        auto vp = view_obj::make_view(child, _w);
        tb.attach(i, *vp->self_wnd_());
    }
}

