// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

	class view_obj;
	using view_ptr = ptr<view_obj>;

	class view_obj : public object
    {
        widget_cfg& cfg_;

        using _Widgets = std::map<id, wnd_ptr>;
        NAR_FIELD(_Widgets, widgets);

		NAR_FIELD(wnd_ptr, self_wnd);

	public:
        view_obj(widget_cfg& _cfg);

        widget_cfg& cfg() { return cfg_; }
        const widget_cfg& cfg() const { return cfg_; }

		void show(bool _visible = true) const;

        void close();

		wnd_ptr get_widget(id _id) const;

		template<class T>
		T& wnd(id _id = {}) const
		{
			if (_id.empty())
                return dynamic_cast<T&>(*m_self_wnd);

            _id = cfg().id_path() / _id;
			wnd_ptr w = get_widget(_id);
			if (!w)
				throw std::invalid_argument("no widget for " + _id.str());
			return dynamic_cast<T&>(*w);
		}

		static view_ptr make_view(widget_cfg& _cfg);

	private:
		static void make_child_widgets(widget_cfg& _cfg, view_obj* _root_view, widget_cfg* _parent_cfg, nana::window _parent_wnd);

		void init();

	};

}
