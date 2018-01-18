// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    using checkbox_ui = nana::checkbox;

    class checkbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(checkbox, widget_cfg);

        NAR_FIELD(optional<bool>, check);
        NAR_FIELD(optional<bool>, radio);
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, check);
            NAR_CODEC(_s, radio);
            NAR_CODEC(_s, transparent);
        }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}