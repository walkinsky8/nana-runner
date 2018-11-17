// Created by walkinsky(lyh6188@hotmail.com), 2018/02/21
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/sample/login_view_impl.h>

#include <nana/runner/sample/login_model.h>

namespace nana::runner::sample {

    class login_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(login_cntrl, controller_obj);

        view_ptr view_;

        login_model model_;

        callback on_login_success_;

    public:
        login_cntrl();
        ~login_cntrl();

        void open(callback _on_login_success) override;

        void close() override;

    private:
        void on_login(const login_model& _model);

        bool check_model() const;

    };

}

