// Created by walkinsky(lyh6188@hotmail.com), 2018/10/19
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/panel.hpp>

#include <nana/runner/view_base.h>

namespace nana::runner {

    using tabframe = nana::panel<true>;
    using tabframe_lite = nana::panel<false>;

    class tabframe_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tabframe, widget_cfg);
        NAR_FIELD(id, tabbar_id);

        mutable std::vector<view_ptr> m_views;

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, tabbar_id);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

        void make_extra_div(string& _div) const override;

    };

    class tabframe_lite_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tabframe_lite, widget_cfg);
        NAR_FIELD(id, tabbar_id);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, tabbar_id);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
