// Created by walkinsky(lyh6188@hotmail.com), 2018/02/21
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/sample/login_view.h>

#include <nana/runner/sample/login_model.h>

#include <nana/runner/app_base.h>

namespace nana::runner::sample {

    class login_ctr : public controller_obj
    {
        view_ptr view_;

        model::login data_;

    public:
        static void init_views()
        {
            add_view<view::login>();
        }

        void init_logic()
        {
            view_ = app::instance().load_view(L"login.nar");
			view_->show();
        }

    };

}

