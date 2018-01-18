// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    using button_ui = nana::button;

    class button_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(button, widget_cfg);

        NAR_FIELD(optional<bool>, enable_pushed);
        NAR_FIELD(optional<bool>, pushed);
        NAR_FIELD(optional<bool>, omitted);
        NAR_FIELD(optional<bool>, enable_focus_color);
        NAR_FIELD(optional<bool>, transparent);
        NAR_FIELD(optional<bool>, edge_effects);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, enable_pushed);
            NAR_CODEC(_s, pushed);
            NAR_CODEC(_s, omitted);
            NAR_CODEC(_s, enable_focus_color);
            NAR_CODEC(_s, transparent);
            NAR_CODEC(_s, edge_effects);
        }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
