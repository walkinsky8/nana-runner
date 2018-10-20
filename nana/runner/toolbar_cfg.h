// Created by walkinsky(lyh6188@hotmail.com), 2018/10/20
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/toolbar.hpp>

namespace nana::runner {

    using toolbar = nana::toolbar;

    class toolbar_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(toolbar, widget_cfg);

        NAR_FIELD(optional<unsigned>, scale);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            NAR_CODEC_SUPER(_s);
            NAR_CODEC(_s, scale);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
