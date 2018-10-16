// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    struct option {};

    class option_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(option, widget_cfg);

        NAR_FIELD(string, file);
        NAR_FIELD(unsigned, width);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, file);
            NAR_CODEC(_s, width);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w) const override { }

    };

}
