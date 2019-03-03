/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/01/25
#pragma once

#include <runa/editor/login_view.h>

#include <runa/editor/login_model.h>

namespace runa::editor {

    class login_view_impl : public login_view
    {
        NAR_DEFINE_VIEW_IMPL(login);

        model_proxy<login_model> proxy_;

    public:
        login_view_impl(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_model_proxy(model_proxy<login_model> const& _proxy);

    private:
        void init();

        void on_login();

        void on_close();

        void load_model();

        void save_model();

    };

}

