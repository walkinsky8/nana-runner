// Created by walkinsky(lyh6188@hotmail.com), 2018/10/19
#include "stdafx.h"

#include "tab_cfg.h"

#include <nana/runner/view_base.h>

nana::runner::tab::tab(window owner, bool visible)
    : super{ owner, visible }
{}

nana::place & nana::runner::tab::get_place()
{
    if (this->empty())
        throw std::runtime_error("tab::get_place(): the tab has destroyed.");

    if (!place_)
        place_.reset(new place{ *this });

    return *place_;
}

void nana::runner::tab::div(const char* div_text)
{
    get_place().div(div_text);
}

nana::place::field_reference nana::runner::tab::operator[](const char* field_name)
{
    return get_place()[field_name];
}

void nana::runner::tab::collocate() noexcept
{
    if (place_)
        place_->collocate();
}

nana::runner::wnd_ptr nana::runner::tab_cfg::create_wnd(window _parent, bool _visible) const
{
    return std::make_shared<ui_type>(_parent, _visible);
}

void nana::runner::tab_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    string div = make_div();
    NAR_LOG_VAR(div);

    auto& w = dynamic_cast<ui_type&>(_w);
    //auto& w = dynamic_cast<tab&>(*_root_view->self_wnd_());

    w.div(div.data());

    for (auto& i : _root_view->widgets_())
    {
        if (i.second)
        {
            //NAR_LOG_VAR(i.first);
            w[i.first.str().data()] << *i.second;
        }
    }

    w.collocate();
}

