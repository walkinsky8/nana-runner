// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/controller_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/sample/logger_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/editor_view.h>
#include <nana/runner/sample/editor_setup_view.h>

#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class editor_ctr : public controller_obj
    {
        view::logger* log_{};
        view::login* login_{};
        view::editor* editor_{};
        view::editor_setup* editor_setup_{};

    public:
        void init_views() override
        {
            add_view<view::logger>();
            add_view<view::login>();
            add_view<view::editor>();
            add_view<view::editor_setup>();
        }

        void init_logic() override
        {
            log_ = get_view<view::logger>();
            login_ = get_view<view::login>();
            editor_ = get_view<view::editor>();
            editor_setup_ = get_view<view::editor_setup>();

            log_->show();
            login_->show();
            login_->on_login([this] { editor_->show(); });
            editor_->on_setup([this] { editor_setup_->show(); });
        }

    };

}

