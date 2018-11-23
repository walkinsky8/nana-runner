// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/menu.hpp>

namespace runa {

    using menu = nana::menu;

    class menu_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(menu, widget_cfg);

        NAR_FIELD(string, image);
        NAR_FIELD(string, _click);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, image);
            NAR_CODEC(_s, _click);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

        void init_menu(menu& _m) const;

    };

}
