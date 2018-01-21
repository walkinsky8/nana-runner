// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_cfg.h>

#include <nana/runner/widget_factory.h>

nana::runner::wnd_ptr nana::runner::widget_cfg::get_widget(id _id) const
{
    auto i = m_widgets.find(_id);
    if (i == m_widgets.end())
        return nullptr;
    return (*i).second;
}

void nana::runner::widget_cfg::make_widgets(widget_cfg& _root_cfg, widget_cfg* _parent_cfg, nana::window _parent_wnd)
{
    set_parent(_parent_cfg);

    wnd_ptr w = create_widget(_parent_wnd, true);

    for (auto& i : m_children)
    {
        i->make_widgets(_root_cfg, this, _parent_wnd);
    }

    if (w)
    {
        init_widget(*w);
        _root_cfg.m_widgets[id_path()] = w;
    }
}

void nana::runner::widget_cfg::make_widgets()
{
    wnd_ptr root_wnd = create_widget(nullptr, true);
    if (!root_wnd)
        throw std::invalid_argument(string("invalid root widget ") + id_path().str());

    for (auto& i : m_children)
    {
        i->make_widgets(*this, this, *root_wnd);
    }

    init_widget(*root_wnd);
    this->m_widgets[id_path()] = root_wnd;
}

void nana::runner::widget_cfg::make_div(string& _div) const
{
    _div << "<" << id_path() << " " << div_();
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

nana::runner::cfg_ptr nana::runner::widget_cfg::from_file(wstring const& _filename)
{
    string cfg;
    if (!read_file(_filename, cfg))
        throw std::invalid_argument("read cfg error: " + to_utf8(_filename));

    parser parsed(cfg);

    cfg_ptr v;
    parsed >> v;

    v->make_widgets();
    return v;
}

void nana::runner::operator >> (const parser& _is, std::shared_ptr<widget_cfg>& _v)
{
    _v = widget_factory::instance().create(_is.type());
    _is >> *_v;
}

void nana::runner::widget_cfg::init_widget(widget& _w) const
{
    _w.caption(get_caption());

    if (!tooltip_().empty())
        _w.tooltip(tooltip_());

    if (!bgcolor_().empty())
        _w.bgcolor(get_color(bgcolor_()));

    if (!fgcolor_().empty())
        _w.fgcolor(get_color(fgcolor_()));

    if (!pos_().empty())
        _w.move(pos_().value());

    if (!size_().empty())
        _w.size(size_().value());

    if (!cursor_().empty())
        _w.cursor(cursor_().value().value());

    if (!typeface_().empty())
        _w.typeface(typeface_().value());

    if (!enabled_().empty())
        _w.enabled(enabled_().value());

    if (!visible_().empty())
        visible_().value() ? _w.show() : _w.hide();
}
