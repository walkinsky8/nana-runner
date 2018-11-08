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
            : view_obj{ _cfg, _parent }
            , username_{ wnd<textbox>("username.value") }
            , password_{ wnd<textbox>("password.value") }
            , login_{ wnd<button>("cmd.login") }
            , close_{ wnd<button>("cmd.close") }
        {
            login_.events().click([this] { on_login(); });
            close_.events().click([this] { on_close(); });
        }

        void on_login(std::function<void()> _f)
        {
            login_.events().click([this, _f] { close(); _f(); });
        }

        void on_login()
        {
            NAR_LOG("login: username=" << username_.caption() << ", password=" << password_.caption());
        }

        void on_close()
        {
            NAR_LOG("close login window");
            close();
            NAR_LOG("login cancelled, so quit program");
            app::quit();
        }

    };

}
