// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/sample/login_view.h>

namespace nana::runner::sample {

    class login_view_impl : public login_view
    {
        NAR_DEFINE_VIEW_IMPL(login);

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

    private:
        void init();

        void on_login();

        void on_close();

    };

}

