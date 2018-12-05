// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/textbox_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa::editor {

    class login_view : public view_obj
    {
        NAR_DEFINE_VIEW(login, view_obj);

    public:
        textbox& username_;
        textbox& password_;
        
        button& login_;
        button& close_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , username_{ wnd<textbox>("username.value") }
            , password_{ wnd<textbox>("password.value") }
            , login_{ wnd<button>("cmd.login") }
            , close_{ wnd<button>("cmd.close") }
        {
        }

    };

}

