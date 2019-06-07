/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/01/22
#pragma once

#include <runa/foundation/font/font_view.h>

#include <runa/foundation/font/font_model.h>

namespace runa {

    class font_view_impl : public font_view
    {
        NAR_DEFINE_VIEW_IMPL(font);

        model_proxy<font_model> model_;

    public:
        font_view_impl(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_model_proxy(model_proxy<font_model> const& _proxy);

    private:
        void init();

        void on_ok();
        void on_cancel();

        void load_model();
        void save_model();

        void on_model_updated();

        font get_font_value() const;

    };

}

