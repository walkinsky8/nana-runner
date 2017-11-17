// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/view_cfg.h>
#include <nana/runner/widget_factory.h>

nana::runner::view_cfg::~view_cfg()
{
    for (auto& i : m_widgets)
    {
        delete i.second;
    }
}

nana::widget* nana::runner::view_cfg::get_widget_(id _id) const
{
    auto i = m_widgets.find(_id);
    if (i == m_widgets.end())
        return nullptr;
    return (*i).second;
}

void nana::runner::view_cfg::make_widgets(view_cfg& _root_cfg, view_cfg* _parent_cfg, nana::window _parent_wnd)
{
    set_parent(_parent_cfg);

    widget* w = create_wnd(_parent_wnd);
    if (w)
    {
        make_widget(*w, *this);
        _root_cfg.m_widgets[id_name()] = w;
    }

    for (auto& i : m_children)
    {
        i.make_widgets(_root_cfg, this, _parent_wnd);
    }
}

void nana::runner::view_cfg::make_widgets(nana::window _parent_wnd)
{
    for (auto& i : m_children)
    {
        i.make_widgets(*this, this, _parent_wnd);
    }
}

void nana::runner::view_cfg::make_div(string& _div) const
{
    _div << "<" << id_name() << " " << div_();
    for (auto& i : m_children)
    {
        i.make_div(_div);
    }
    _div << ">";
}

std::string nana::runner::view_cfg::get_caption() const
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

void nana::runner::view_cfg::from_file(wstring const& _filename)
{
    string cfg;
    if (!read_file(_filename, cfg))
        throw std::invalid_argument("read cfg error: " + to_utf8(_filename));

    parser parsed(cfg);

    parsed >> *this;
}

nana::widget * nana::runner::view_cfg::create_wnd(nana::window _parent_wnd, bool _visible) const
{
    return create_widget(__type_(), _parent_wnd, _visible);
}

void nana::runner::make_widget(widget& _w, view_cfg& _cfg)
{
    _w.caption(_cfg.get_caption());

    if (!_cfg.bgcolor_().empty())
        _w.bgcolor(get_color(_cfg.bgcolor_()));

    if (!_cfg.fgcolor_().empty())
        _w.fgcolor(get_color(_cfg.fgcolor_()));
}

void nana::runner::make_form(form& _f, view_cfg& _cfg)
{
    make_widget(_f, _cfg);

    string div = _cfg.make_div();
    NAR_LOG_VAR(div);

    _f.div(div.data());

    for (auto& i : _cfg.widgets_())
    {
        _f[i.first.str().data()] << *_cfg.get_widget_(i.first);
    }

    _f.collocate();
}

