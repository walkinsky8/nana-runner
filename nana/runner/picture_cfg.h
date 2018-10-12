// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/picture.hpp>

namespace nana::runner {

    using picture = nana::picture;

    class picture_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(picture, widget_cfg);

        NAR_FIELD(string, file);
        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);
        NAR_FIELD(string, gradual_from);
        NAR_FIELD(string, gradual_to);
        NAR_FIELD(optional<bool>, gradual_horizontal);
        NAR_FIELD(optional<bool>, stretchable);
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, file);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
            NAR_CODEC(_s, gradual_from);
            NAR_CODEC(_s, gradual_to);
            NAR_CODEC(_s, gradual_horizontal);
            NAR_CODEC(_s, stretchable);
            NAR_CODEC(_s, transparent);
        }

        static wnd_ptr create_wnd_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}