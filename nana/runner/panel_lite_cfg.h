// Created by walkinsky(lyh6188@hotmail.com), 2018/10/20
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/panel.hpp>

namespace nana::runner {

    using panel_lite = nana::panel<false>;

    class panel_lite_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(panel_lite, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

        bool has_child_div() const override { return true; }

    };

}
