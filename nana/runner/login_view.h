// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::view {

    class Login : public view_obj
    {
        widget_cfg& cfg_;

        textbox& username_;
        textbox& password_;
        
        button& login_;
        button& close_;

    public:
        static string type_name_() { return "login"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Login>(_cfg); }

    public:
        Login(widget_cfg& _cfg)
            : cfg_{ _cfg }
            , username_{ _cfg.wnd<textbox>("username.value") }
            , password_{ _cfg.wnd<textbox>("password.value") }
            , login_{ _cfg.wnd<button>("cmd.login") }
            , close_{ _cfg.wnd<button>("cmd.close") }
        {
            login_.events().click([this] { on_login(); });
            close_.events().click([this] { on_close(); });
        }

        void on_login()
        {
            NAR_LOG("login: username=" << username_.caption() << ", password=" << password_.caption());
        }

        void on_close()
        {
            NAR_LOG("close login window");
            cfg_.close();
        }

    };

}
