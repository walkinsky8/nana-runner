// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/group.hpp>

namespace nana::runner {

    using group = nana::group;

    class group_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(group, widget_cfg);

        NAR_FIELD(optional<align>, caption_align);
        NAR_FIELD(optional<bool>, radio_mode);
        NAR_FIELD(optional<bool>, enable_format_caption);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, caption_align);
            NAR_CODEC(_s, radio_mode);
            NAR_CODEC(_s, enable_format_caption);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, nana::rectangle{}, v); }

        void init_widget(widget& _w) const override;

        bool has_child_div() const override { return false; }

    };

}
