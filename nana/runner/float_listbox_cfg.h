// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/float_listbox.hpp>

namespace runa {

    using float_listbox = nana::float_listbox;

    class float_listbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(float_listbox, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, nana::API::make_center(300,200), true); }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

    };

}
