// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample {

    class login_view : public view_obj
    {
        NAR_DEFINE_VIEW(login, view_obj);

    public:
        textbox& username_;
        textbox& password_;
        
        button& login_;
        button& close_;

    public:
        login_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , username_{ wnd<textbox>("username.value") }
            , password_{ wnd<textbox>("password.value") }
            , login_{ wnd<button>("cmd.login") }
            , close_{ wnd<button>("cmd.close") }
        {
            init();
        }

        void set_on_login(std::function<void()> _f);

    private:
        void init();

        void on_login();

        void on_close();

    };

}
