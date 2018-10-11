// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/form.hpp>

namespace nana::runner {

    using form = nana::form;

    class form_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(form, widget_cfg);

        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
        }

        static wnd_ptr create_wnd_(window p, bool v) { return std::make_shared<ui_type>(p); }

        void init_widget(widget& _w) const override;

        void on_init_view(widget& _w, const std::map<id, wnd_ptr>& _widgets) const override;

        point get_pos() const override;

    };

}
