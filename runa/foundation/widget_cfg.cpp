/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/widget_cfg.h>

#include <runa/foundation/widget_factory.h>

#include <runa/foundation/app_base.h>

void runa::widget_cfg::make_div(string& _div) const
{
    _div << "<" << id_path() << " " << div_();
    if (has_child_div())
    {
        for (auto& i : m_children)
        {
            if (i)
                i->make_div(_div);
        }
    }
    make_extra_div(_div);
    _div << ">";
}

runa::id runa::widget_cfg::id_path() const
{
    return get_id_path(true);
}

runa::id runa::widget_cfg::get_id_path(bool _self_node) const
{
    if (!m_parent)
        return id_();
    if (id_().empty())
    {
        if (_self_node)
            return id_();
        return m_parent->get_id_path(false);
    }
    return m_parent->get_id_path(false) / id_();
}

void runa::widget_cfg::reset_all_parent(widget_cfg* _parent)
{
    set_parent(_parent);

    for (auto& i : m_children)
        i->reset_all_parent(this);
}

runa::point runa::widget_cfg::get_pos(size) const
{
    return pos_().value();
}

std::string runa::widget_cfg::get_caption() const
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

runa::widget_cfg* runa::widget_cfg::get_parent_or_global() const
{
    if (m_parent)
        return m_parent;
    cfg_ptr glob = get_generic();
    if (glob)
        return glob.get();
    return nullptr;
}

const runa::string& runa::widget_cfg::get_fgcolor() const
{
    if (!fgcolor_().empty())
        return fgcolor_();
    auto p = get_parent_or_global();
    if (p)
        return p->get_fgcolor();
    return fgcolor_();
}

const runa::string& runa::widget_cfg::get_bgcolor() const
{
    if (!bgcolor_().empty())
        return bgcolor_();
    auto p = get_parent_or_global();
    if (p)
        return p->get_bgcolor();
    return bgcolor_();
}

const runa::optional<runa::cursor>& runa::widget_cfg::get_cursor() const
{
    if (!cursor_().empty())
        return cursor_();
    auto p = get_parent_or_global();
    if (p)
        return p->get_cursor();
    return cursor_();
}

const runa::optional<runa::font>& runa::widget_cfg::get_typeface() const
{
    if (!typeface_().empty())
        return typeface_();
    auto p = get_parent_or_global();
    if (p)
        return p->get_typeface();
    return typeface_();
}

runa::cfg_ptr runa::widget_cfg::get_generic()
{
    return app::instance().find_cfg("generic");
}

runa::cfg_ptr runa::widget_cfg::from(string const& _cfg)
{
    parser parsed(_cfg);

    cfg_ptr p;
    parsed >> p;

    if (!p)
    {
        NAR_LOG_ERROR("no widget type @" << parsed.type());
    }
    return p;
}

void runa::operator >> (const parser& _is, cfg_ptr& _v)
{
    _v = widget_factory::instance().create(_is.type());
    if (_v)
    {
        _is >> *_v;
        _v->reset_all_parent(nullptr);
    }
}

void runa::widget_cfg::init_widget(widget& _w, view_obj* _root_view) const
{
    _w.caption(get_caption());

    if (!tooltip_().empty())
        _w.tooltip(tooltip_());

    auto& bg = get_bgcolor();
    if (!bg.empty())
        _w.bgcolor(get_color(bg, _w.bgcolor()));

    auto& fg = get_fgcolor();
    if (!fg.empty())
        _w.fgcolor(get_color(fg, _w.fgcolor()));

    if (!size_().empty())
        _w.size(size_().value());

    //always call get_pos() to support user defined center align.
    //if (!pos_().empty())
        _w.move(get_pos(_w.size()));

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

#endif

