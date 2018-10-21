// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/view_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/generic_view.h>

nana::runner::view_obj::view_obj(widget_cfg& _cfg, window _parent)
    : m_cfg{ _cfg }, m_parent_wnd{ _parent }
{
    init(!_cfg.visible_().empty() && _cfg.visible_().value(), _parent);
}

void nana::runner::view_obj::show(bool _visible) const
{
	if (m_self_wnd)
	{
		if (_visible)
			m_self_wnd->show();
		else
			m_self_wnd->hide();
	}
}

void nana::runner::view_obj::close()
{
    if (m_self_wnd)
    {
        m_self_wnd->close();
    }
}

void nana::runner::view_obj::add_widget(wnd_ptr _w, widget_cfg& _cfg)
{
    id path_in_root_view = _cfg.id_path();
    NAR_LOG_VAR(path_in_root_view);
    m_widgets[path_in_root_view] = _w;
    m_cfgs[path_in_root_view] = &_cfg;

}

void nana::runner::view_obj::add_child_view(id _id, view_ptr _vw)
{
    m_child_views[_id] = _vw;
}

nana::runner::wnd_ptr nana::runner::view_obj::get_widget(id _id) const
{
	auto i = m_widgets.find(_id);
	if (i == m_widgets.end())
		return nullptr;
	return (*i).second;
}

nana::runner::widget_cfg* nana::runner::view_obj::get_cfg(id _id) const
{
    auto i = m_cfgs.find(_id);
    if (i == m_cfgs.end())
        return nullptr;
    return (*i).second;
}

nana::runner::widget_cfg* nana::runner::view_obj::cfg_(id _id) const
{
    if (_id.empty())
        return &m_cfg;

    _id = cfg().id_path() / _id;
    return get_cfg(_id);
}

void nana::runner::view_obj::make_child_widgets(widget_cfg& _cfg, view_obj* _root_view, widget_cfg* _parent_cfg, nana::window _parent_wnd, bool _visible)
{
    if (_cfg.id_().empty() || !_cfg.has_ui_widget())
        return;

	auto& w = _cfg.create_wnd(_parent_wnd, _visible);
	if (!w)
		throw std::invalid_argument(string("invalid widget ") + _cfg.id_path().str());

    if (_cfg.has_child_div())
	    for (auto& i : _cfg.children_())
	    {
            if (i)
		        make_child_widgets(*i, _root_view, &_cfg, _parent_wnd, true);
	    }

	_cfg.init_widget(*w, _root_view);

    _root_view->add_widget(w, _cfg);
}

void nana::runner::view_obj::init(bool _visible, window _parent)
{
    NAR_LOG_VAR(cfg().get_caption());

    m_self_wnd = cfg().create_wnd(_parent, _visible);
    if (!m_self_wnd)
        throw std::invalid_argument(string("invalid root widget ") + cfg().id_path().str());

    for (auto& i : cfg().children_())
    {
        if (i)
            make_child_widgets(*i, this, &cfg(), *m_self_wnd/*not _parent!!!*/, true);
    }

    cfg().init_widget(*m_self_wnd, this);
}

nana::runner::view_ptr nana::runner::view_obj::make_view(widget_cfg& _cfg, window _parent)
{
    view_ptr p = create_view(_cfg, _parent);
    if (p)
        return p;
    return std::make_shared<view::Generic>(_cfg, _parent);
}

