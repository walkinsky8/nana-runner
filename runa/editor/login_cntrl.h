// Created by walkinsky(lyh6188@hotmail.com), 2018/02/21
#pragma once

#include <runa/foundation/controller_base.h>

#include <runa/editor/login_view_impl.h>

#include <runa/editor/login_model.h>

namespace runa::editor {

    class login_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(login_cntrl, controller_obj);

        view_ptr view_;

        login_model model_;

        callback on_login_success_;

    public:
        login_cntrl();
        ~login_cntrl();

        void open(callback _on_login_success);

        void close();

    private:
        void on_login(const login_model& _model);

        bool check_model() const;

    };

}

