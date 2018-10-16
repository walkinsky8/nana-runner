// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/progress.hpp>

namespace nana::runner {

    using progress = nana::progress;

    class progress_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(progress, widget_cfg);

        NAR_FIELD(size_t, amount);
        NAR_FIELD(size_t, value);
        NAR_FIELD(bool, unknown);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, amount);
            NAR_CODEC(_s, value);
            NAR_CODEC(_s, unknown);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
