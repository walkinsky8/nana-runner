// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    using textbox_ui = nana::textbox;

    class textbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(textbox, widget_cfg);

        NAR_FIELD(optional<bool>, line_wrapped);
        NAR_FIELD(optional<bool>, multi_lines);
        NAR_FIELD(optional<bool>, editable);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, line_wrapped);
            NAR_CODEC(_s, multi_lines);
            NAR_CODEC(_s, editable);
        }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
