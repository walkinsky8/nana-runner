// Created by walkinsky(lyh6188@hotmail.com), 2018/11/25
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/runner/color_chooser.h>

namespace runa {

    class color_chooser_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(color_chooser, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
