// Created by walkinsky(lyh6188@hotmail.com), 2018/10/19
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "tab_cfg.h"

#include <nana/runner/view_base.h>

runa::tab::tab(window owner, bool visible)
    : super{ owner, visible }
{}

nana::place & runa::tab::get_place()
{
    if (this->empty())
        NAR_THROW_ERROR(std::runtime_error, "the tab has destroyed.");

    if (!place_)
        place_.reset(new place{ *this });

    return *place_;
}

void runa::tab::div(const char* div_text)
{
    get_place().div(div_text);
}

nana::place::field_reference runa::tab::operator[](const char* field_name)
{
    return get_place()[field_name];
}

void runa::tab::collocate() noexcept
{
    if (place_)
        place_->collocate();
}

runa::wnd_ptr runa::tab_cfg::create_wnd(window _parent, bool _visible) const
{
    return std::make_shared<ui_type>(_parent, _visible);
}

void runa::tab_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    string div = make_div();
    NAR_LOG_VAR(div);

    auto& w = dynamic_cast<ui_type&>(_w);
    //auto& w = dynamic_cast<tab&>(*_root_view->self_wnd_());

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

#endif

