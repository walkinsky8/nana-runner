// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/panel.hpp>

namespace nana::runner {

    using panel = nana::panel<true>;

    class panel_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(panel, widget_cfg);

        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, transparent);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

        bool has_child_div() const override { return true; }

    };

}
