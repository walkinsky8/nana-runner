// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/sample/login_view.h>

#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class login_view_impl : public login_view
    {
        NAR_DEFINE_VIEW_IMPL(login);

        model_proxy<login_model> proxy_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_model_proxy(model_proxy<login_model> const& _proxy);

        void load_model(const login_model& _model);

        void save_model(login_model& _model) const;

    private:
        void init();

        void on_login();

        void on_close();

    };

}

