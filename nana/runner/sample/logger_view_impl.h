// Created by walkinsky(lyh6188@hotmail.com), 2018/11/12
#pragma once

#include <nana/runner/sample/logger_view.h>

namespace nana::runner::sample {

    class logger_view_impl : public logger_view
    {
        NAR_DEFINE_VIEW_IMPL(logger);

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

    private:
        void init();

    };

}

