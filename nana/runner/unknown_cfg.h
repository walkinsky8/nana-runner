// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    struct unknown {};

    class unknown_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(unknown, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

    };

}
