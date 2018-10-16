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
        NAR_FIELD(optional<bool>, taskbar);
        NAR_FIELD(optional<bool>, floating);
        NAR_FIELD(optional<bool>, no_activate);
        NAR_FIELD(optional<bool>, minimize);
        NAR_FIELD(optional<bool>, maximize);
        NAR_FIELD(optional<bool>, sizable);
        NAR_FIELD(optional<bool>, decoration);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
            NAR_CODEC(_s, taskbar);
            NAR_CODEC(_s, floating);
            NAR_CODEC(_s, no_activate);
            NAR_CODEC(_s, minimize);
            NAR_CODEC(_s, maximize);
            NAR_CODEC(_s, sizable);
            NAR_CODEC(_s, decoration);
        }

        wnd_ptr create_wnd(window p, bool v) const override;

        void init_widget(widget& _w) const override;

        void on_init_view(widget& _w, const std::map<id, wnd_ptr>& _widgets) const override;

        bool has_child_div() const override { return true; }

        point get_pos() const override;

    };

}
