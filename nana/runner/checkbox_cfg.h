// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/checkbox.hpp>

namespace nana::runner {

    using checkbox = nana::checkbox;

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

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
