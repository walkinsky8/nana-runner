// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/app_base.h>

#include <nana/runner/sample/login_cntrl.h>
#include <nana/runner/sample/editor_cntrl.h>
#include <nana/runner/sample/demo_cntrl.h>

namespace runa::sample {

    class editor_app : public app
    {
        login_cntrl login_;
        editor_cntrl editor_;
        demo_cntrl demo_;

    public:
        editor_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}

