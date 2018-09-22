// Created by walkinsky(lyh6188@hotmail.com), 2018/02/21
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/controller_base.h>
#include <nana/runner/view_factory.h>

#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class login_ctr : public controller_obj
    {
        view::login* view_{};

        model::login data_;

    public:
        void init_views() override
        {
            add_view<view::login>();
        }

        void init_logic() override
        {
            view_ = get_view<view::login>();
            view_->show();
        }

    };

}

