// Created by walkinsky(lyh6188@hotmail.com), 2018/02/21
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/sample/login_view.h>

#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class login_cntrl : public controller_obj
    {
        view_ptr view_;

        login_model data_;

    public:
        static void initialize();

        void on_init() override;

        void on_fini() override;

    };

}

