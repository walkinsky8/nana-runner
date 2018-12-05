// Created by walkinsky(lyh6188@hotmail.com), 2018/11/12
#pragma once

#include <runa/editor/logger_view.h>

namespace runa::editor {

    class logger_view_impl : public logger_view
    {
        NAR_DEFINE_VIEW_IMPL(logger);

        log_handler::func_ptr log_handler_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void init_log_handler();

    private:
        void init();

        void on_fini() override;

    };

}

