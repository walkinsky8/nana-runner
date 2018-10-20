// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    struct option {};

    class option_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(option, widget_cfg);

        NAR_FIELD(string, image);
        NAR_FIELD(optional<unsigned>, width);
        NAR_FIELD(optional<bool>, check);
        NAR_FIELD(string, _click);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, image);
            NAR_CODEC(_s, width);
            NAR_CODEC(_s, check);
            NAR_CODEC(_s, _click);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

        bool has_ui_widget() const override { return false; }

        bool empty() const
        {
            return id_().empty() && caption_().empty() && !children_().size();
        }

    };

}
