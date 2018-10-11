// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/sample/logger_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/editor_view.h>
#include <nana/runner/sample/editor_setup_view.h>

#include <nana/runner/sample/login_model.h>

#include <nana/runner/app_base.h>

namespace nana::runner::sample {

    class editor_ctr : public controller_obj
    {
        view_ptr log_;
		view_ptr login_;
		view_ptr editor_;
		view_ptr editor_setup_;

    public:
		static void initialize()
		{
			add_view<view::logger>();
			add_view<view::login>();
			add_view<view::editor>();
			add_view<view::editor_setup>();
        }

        void on_init() override
        {
			log_ = app::get_view(L"logger.nar");
			login_ = app::get_view(L"login.nar");
			editor_ = app::get_view(L"editor.nar");
			editor_setup_ = app::get_view(L"editor_setup.nar");

            log_->show();
            login_->show();
            login_->cast<view::login>().on_login([this] { editor_->show(); });
            editor_->cast<view::editor>().on_setup([this] { editor_setup_->show(); });
        }

        void on_fini() override
        {
            log_->close();
            login_->close();
            editor_->close();
            editor_setup_->close();
        }

    };

}

