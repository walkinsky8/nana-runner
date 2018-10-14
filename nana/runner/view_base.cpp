// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/view_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/generic_view.h>

nana::runner::view_obj::view_obj(widget_cfg& _cfg)
    : cfg_{ _cfg }
{
    init(!_cfg.visible_().empty() && _cfg.visible_().value());
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

nana::runner::wnd_ptr nana::runner::view_obj::get_widget(id _id) const
{
	auto i = m_widgets.find(_id);
	if (i == m_widgets.end())
		return nullptr;
	return (*i).second;
}

void nana::runner::view_obj::make_child_widgets(widget_cfg& _cfg, view_obj* _root_view, widget_cfg* _parent_cfg, nana::window _parent_wnd, bool _visible)
{
	_cfg.set_parent(_parent_cfg);

	auto& w = _cfg.create_wnd(_parent_wnd, _visible);
	if (!w)
		throw std::invalid_argument(string("invalid widget ") + _cfg.id_path().str());

	for (auto& i : _cfg.children_())
	{
        if (i && !i->id_().empty())
		    make_child_widgets(*i, _root_view, &_cfg, _parent_wnd, _visible);
	}

	if (!_cfg.id_().empty())
	{
		_cfg.init_widget(*w);

		_root_view->m_widgets[_cfg.id_path()] = w;
	}
}

void nana::runner::view_obj::init(bool _visible)
{
    m_self_wnd = cfg().create_wnd(nullptr, _visible);
    if (!m_self_wnd)
        throw std::invalid_argument(string("invalid root widget ") + cfg().id_path().str());

    if (_visible)
        m_self_wnd->show();

    for (auto& i : cfg().children_())
    {
        if (i && !i->id_().empty())
            make_child_widgets(*i, this, &cfg(), *m_self_wnd, _visible/*true*/);
    }

    cfg().init_widget(*m_self_wnd);

    cfg().on_init_view(*m_self_wnd, m_widgets);
}

nana::runner::view_ptr nana::runner::view_obj::make_view(widget_cfg& _cfg)
{
    view_ptr p = create_view(_cfg);
    if (p)
        return p;
    return std::make_shared<view::Generic>(_cfg);
}

