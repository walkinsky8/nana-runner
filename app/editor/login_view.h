/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/25
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/textbox_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa { namespace editor {

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
        }

    };

}}

