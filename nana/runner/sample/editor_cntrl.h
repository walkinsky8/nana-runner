// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class editor_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(editor_cntrl, controller_obj);

        view_ptr log_;
		view_ptr login_;
		view_ptr editor_;
		view_ptr editor_setup_;

    public:
        static void initialize();

        void on_init() override;

        void on_fini() override;

    };

}

