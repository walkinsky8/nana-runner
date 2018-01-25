// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_cfg.h>

#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

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
    m_root_wnd = create_widget(nullptr, true);
    if (!m_root_wnd)
        throw std::invalid_argument(string("invalid root widget ") + id_path().str());

    for (auto& i : m_children)
    {
        i->make_widgets(*this, this, *m_root_wnd);
    }

    init_widget(*m_root_wnd);

    m_widgets[id_path()] = m_root_wnd;

    m_view = create_view(*this);

    show();
}

void nana::runner::widget_cfg::show() const
{
    if (m_root_wnd)
        m_root_wnd->show();
}

void nana::runner::widget_cfg::close() const
{
    if (m_root_wnd)
        m_root_wnd->close();
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

const nana::runner::string& nana::runner::widget_cfg::get_fgcolor() const
{
    if (!fgcolor_().empty())
        return fgcolor_();
    if (m_parent)
        return m_parent->get_fgcolor();
    return fgcolor_();
}

const nana::runner::string& nana::runner::widget_cfg::get_bgcolor() const
{
    if (!bgcolor_().empty())
        return bgcolor_();
    if (m_parent)
        return m_parent->get_bgcolor();
    return bgcolor_();
}

const nana::runner::optional<nana::runner::cursor>& nana::runner::widget_cfg::get_cursor() const
{
    if (!cursor_().empty())
        return cursor_();
    if (m_parent)
        return m_parent->get_cursor();
    return cursor_();
}

const nana::runner::optional<nana::runner::font>& nana::runner::widget_cfg::get_typeface() const
{
    if (!typeface_().empty())
        return typeface_();
    if (m_parent)
        return m_parent->get_typeface();
    return typeface_();
}

nana::runner::cfg_ptr nana::runner::widget_cfg::from_file(wstring const& _filename)
{
    string cfg;
    if (!read_file(_filename, cfg))
        throw std::invalid_argument("read cfg error: " + to_utf8(_filename));

    parser parsed(cfg);

    cfg_ptr v;
    parsed >> v;
    if (v)
    {
        v->make_widgets();
    }
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

    auto& bg = get_bgcolor();
    if (!bg.empty())
        _w.bgcolor(get_color(bg));

    auto& fg = get_fgcolor();
    if (!fg.empty())
        _w.fgcolor(get_color(fg));

    if (!pos_().empty())
        _w.move(pos_().value());

    if (!size_().empty())
        _w.size(size_().value());

    auto& c = get_cursor();
    if (!c.empty())
        _w.cursor(c.value().value());

    auto& f = get_typeface();
    if (!f.empty())
        _w.typeface(f.value());

    if (!enabled_().empty())
        _w.enabled(enabled_().value());

    if (!visible_().empty())
        visible_().value() ? _w.show() : _w.hide();
}
