// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/app_base.h>

#include <nana/runner/sample/editor_cntrl.h>

namespace nana::runner::sample {

    class editor_app : public app
    {
		editor_cntrl editor_;

    public:
        editor_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}

