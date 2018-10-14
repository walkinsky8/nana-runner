// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/app_base.h>

#include <nana/runner/sample/editor_ctr.h>

#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/color_view.h>
#include <nana/runner/sample/font_view.h>

namespace nana::runner::sample {

    class editor_app : public app
    {
		editor_ctr editor_;

    public:
        editor_app()
        {
            editor_ctr::initialize();

            add_view<view::Demo>();
            add_view<view::Hello>();
            add_view<view::Color>();
            add_view<view::Font>();
        }

        void on_init() override
		{
			editor_.on_init();
		}

        void on_fini() override
        {
            editor_.on_fini();
        }

    };

}

