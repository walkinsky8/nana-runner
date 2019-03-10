/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/12
#pragma once

#include <runa/editor/logger_view.h>

namespace runa { namespace editor {

    class logger_view_impl : public logger_view
    {
        NAR_DEFINE_VIEW_IMPL(logger);

        log_handler::func_ptr log_handler_;

    public:
        logger_view_impl(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void init_log_handler();

    private:
        void init();

        void on_fini() override;

    };

}}

