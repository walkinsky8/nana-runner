// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/object.h>

#include <nana/runner/widget_cfg.h>

#define NAR_DEFINE_VIEW(_class, _super) \
        private: \
            using super = _super; \
            using self = _class##_view; \
        public: \
            static pcstr type_name_() { return #_class; } \
            static view_ptr new_(widget_cfg& _cfg, window _parent) { return std::make_shared<self>(_cfg, _parent); } \
        public: \
            string type_name() const override { return type_name_(); } \
            dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); } \
            void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); } \
        private:

namespace nana::runner {

	class view_obj;
	using view_ptr = ptr<view_obj>;

	class view_obj : public object
    {
        widget_cfg& m_self_cfg;

        using _Widgets = std::map<id, wnd_ptr>;
        NAR_FIELD(_Widgets, child_widgets);

        using _Cfgs = std::map<id, widget_cfg*>;
        NAR_FIELD(_Cfgs, child_cfgs);

        using _Views = std::map<id, view_ptr>;
        NAR_FIELD(_Views, child_views);

        NAR_FIELD(wnd_ptr, self_wnd);

        NAR_FIELD(window, parent_wnd);

	public:
        view_obj(widget_cfg& _cfg, window _parent);

		void show(bool _visible = true) const;

        void close();

        template<class T>
        T& wnd(id _id = {}) const
        {
            wnd_ptr w = get_widget(_id);
            if (!w)
                throw std::invalid_argument("no widget for " + (m_self_cfg.id_path() / _id).str());
            return dynamic_cast<T&>(*w);
        }

        wnd_ptr get_widget(id _id = {}) const;

        wnd_ptr find_child_widget(id _id) const;

        widget_cfg* cfg(id _id = {}) const;

        widget_cfg* find_child_cfg(id _id) const;

        view_obj const* child_view(id _id) const;

        void add_child_widget(wnd_ptr _w, widget_cfg& _cfg);

        void add_child_view(id _id, view_ptr _vw);

        static view_ptr make_view(widget_cfg& _cfg, window _parent);

    private:
		static void make_child_widgets(widget_cfg& _cfg, view_obj* _root_view, widget_cfg* _parent_cfg, nana::window _parent_wnd, bool _visible);

		void init(bool _visible, window _parent);

    };

}
