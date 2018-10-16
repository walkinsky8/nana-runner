// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/menubar.hpp>

namespace nana::runner {

    using menubar = nana::menubar;

    class menubar_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(menubar, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p); }

        void init_widget(widget& _w) const override;

    };

}
