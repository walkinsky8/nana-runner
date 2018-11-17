// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/view_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/generic_view.h>

nana::runner::view_obj::view_obj(widget_cfg& _cfg, window _parent)
    : m_self_cfg{ _cfg }, m_parent_wnd{ _parent }
{
    init(!_cfg.visible_().empty() && _cfg.visible_().value(), _parent);
}

void nana::runner::view_obj::show(bool _visible) const
{
    wnd_ptr p = m_self_wnd;
	if (p)
	{
		if (_visible)
			p->show();
		else
			p->hide();
	}
}

void nana::runner::view_obj::close()
{
    on_fini();

    wnd_ptr p = m_self_wnd;
    if (p)
    {
        p->close();
    }
}

void nana::runner::view_obj::add_child_widget(wnd_ptr _w, widget_cfg& _cfg)
{
    id path_in_root_view = _cfg.id_path();
    //NAR_LOG_DEBUG(path_in_root_view);
    m_child_widgets[path_in_root_view] = _w;
    m_child_cfgs[path_in_root_view] = &_cfg;

}

void nana::runner::view_obj::add_child_view(id _id, view_ptr _vw)
{
    m_child_views[_id] = _vw;
}

nana::runner::wnd_ptr nana::runner::view_obj::find_child_widget(id _id) const
{
	auto i = m_child_widgets.find(_id);
    return (i != m_child_widgets.end()) ? (*i).second : nullptr;
}

nana::runner::wnd_ptr nana::runner::view_obj::get_widget(id _id) const
{
    if (_id.empty())
        return m_self_wnd;

    _id = m_self_cfg.id_path() / _id;
    return find_child_widget(_id);
}

nana::runner::widget_cfg* nana::runner::view_obj::find_child_cfg(id _id) const
{
    auto i = m_child_cfgs.find(_id);
    return (i != m_child_cfgs.end()) ? (*i).second : nullptr;
}

nana::runner::widget_cfg* nana::runner::view_obj::cfg(id _id) const
{
    if (_id.empty())
        return &m_self_cfg;

    _id = m_self_cfg.id_path() / _id;
    return find_child_cfg(_id);
}

nana::runner::view_obj const * nana::runner::view_obj::child_view(id _id) const
{
    if (_id.empty())
        return this;
    _id = m_self_cfg.id_path() / _id;
    auto i = m_child_views.find(_id);
    if (i == m_child_views.end())
        return nullptr;
    return (*i).second.get();
}

void nana::runner::view_obj::make_child_widgets(widget_cfg& _cfg, view_obj* _root_view, widget_cfg* _parent_cfg, nana::window _parent_wnd, bool _visible)
{
    NAR_LOG_DEBUG(_cfg.id_path());
    if (_cfg.id_().empty() || !_cfg.has_ui_widget())
        return;

	auto& w = _cfg.create_wnd(_parent_wnd, _visible);
	if (!w)
        NAR_THROW_ERROR(std::invalid_argument, "no wnd created for @" << _cfg.type_name());

    if (_cfg.has_child_div())
	    for (auto& i : _cfg.children_())
	    {
            if (i)
		        make_child_widgets(*i, _root_view, &_cfg, _parent_wnd, true);
	    }

	_cfg.init_widget(*w, _root_view);

    _root_view->add_child_widget(w, _cfg);
}

void nana::runner::view_obj::init(bool _visible, window _parent)
{
    //NAR_LOG_DEBUG(cfg().get_caption());

    m_self_wnd = m_self_cfg.create_wnd(_parent, _visible);
    if (!m_self_wnd)
        NAR_THROW_ERROR(std::invalid_argument, "no wnd created for @" << m_self_cfg.type_name());

    for (auto& i : m_self_cfg.children_())
    {
        if (i)
            make_child_widgets(*i, this, &m_self_cfg, *m_self_wnd/*not _parent!!!*/, true);
    }

    m_self_cfg.init_widget(*m_self_wnd, this);
}

nana::runner::view_ptr nana::runner::view_obj::make_view(widget_cfg& _cfg, window _parent)
{
    view_ptr p = create_view(_cfg, _parent);
    if (p)
        return p;
    NAR_LOG_INFO("no view found, use default generic view: "<<_cfg.id_path());
    return std::make_shared<generic_view>(_cfg, _parent);
}

#endif

