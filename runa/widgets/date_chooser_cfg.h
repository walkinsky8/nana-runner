// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/date_chooser.hpp>

namespace runa {

    using date_chooser = nana::date_chooser;

    class date_chooser_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(date_chooser, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

    };

}
