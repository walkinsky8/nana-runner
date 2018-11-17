// Created by walkinsky(lyh6188@hotmail.com), 2018/11/15
#pragma once

#include <nana/runner/app_base.h>

#include <nana/runner/sample/demo_cntrl.h>

namespace nana::runner::sample {

    class demo_app : public app
    {
        demo_cntrl demo_;

    public:
        demo_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}

