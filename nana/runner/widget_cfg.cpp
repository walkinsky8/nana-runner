// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_cfg.h>

#include <nana/runner/widget_factory.h>

nana::widget* nana::runner::widget_cfg::get_widget_(id _id) const
{
    auto i = m_widgets.find(_id);
    if (i == m_widgets.end())
        return nullptr;
    return (*i).second.get();
}

void nana::runner::widget_cfg::make_widgets(widget_cfg& _root_cfg, widget_cfg* _parent_cfg, nana::window _parent_wnd)
{
    set_parent(_parent_cfg);

    widget* w = create_wnd(_parent_wnd);
    if (w)
    {
        init_widget(*w);
        _root_cfg.m_widgets[id_name()].reset(w);
    }

    for (auto& i : m_children)
    {
        i->make_widgets(_root_cfg, this, _parent_wnd);
    }
}

void nana::runner::widget_cfg::make_widgets(nana::window _parent_wnd)
{
    for (auto& i : m_children)
    {
        i->make_widgets(*this, this, _parent_wnd);
    }
}

void nana::runner::widget_cfg::make_div(string& _div) const
{
    _div << "<" << id_name() << " " << div_();
    for (auto& i : m_children)
    {
        i->make_div(_div);
    }
    _div << ">";
}

std::string nana::runner::widget_cfg::get_caption() const
{
    if (!caption_().empty())
    {
        if (caption_() == "null")
            return{};
        return caption_();
    }
    if (id_().empty())
        return id_().str();
    return to_upper(id_().str()[0]) + id_().str().substr(1);
}

void nana::runner::widget_cfg::from_file(wstring const& _filename)
{
    string cfg;
    if (!read_file(_filename, cfg))
        throw std::invalid_argument("read cfg error: " + to_utf8(_filename));

    parser parsed(cfg);

    parsed >> *this;
}

nana::widget * nana::runner::widget_cfg::create_wnd(nana::window _parent_wnd, bool _visible) const
{
    return widget_factory::create_widget(type_name(), _parent_wnd, _visible);
}

void nana::runner::widget_cfg::init_widget(widget& _w) const
{
    _w.caption(get_caption());

    if (!bgcolor_().empty())
        _w.bgcolor(get_color(bgcolor_()));

    if (!fgcolor_().empty())
        _w.fgcolor(get_color(fgcolor_()));
}
