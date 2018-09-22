// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/app_base.h>

#include <nana/runner/sample/editor_ctr.h>

namespace nana::runner::sample {

    class editor_app : public app
    {
        logger* log_{};
        login* login_{};
        editor* editor_{};
        editor_setup* editor_setup_{};

    public:
        void init_views() override
        {
            add_view<logger>();
            add_view<login>();
            add_view<editor>();
            add_view<editor_setup>();
        }

        void init_logic() override
        {
            log_ = get_view<logger>();
            login_ = get_view<login>();
            editor_ = get_view<editor>();
            editor_setup_ = get_view<editor_setup>();

            log_->show();
            login_->show();
            login_->on_login([this] { editor_->show(); });
            editor_->on_setup([this] { editor_setup_->show(); });
        }

    };

}

