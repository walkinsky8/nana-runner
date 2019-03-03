/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/02/11
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/textbox_cfg.h>
#include <runa/widgets/combox_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa::editor {

    class editor_setup_view : public view_obj
    {
        NAR_DEFINE_VIEW(editor_setup, view_obj);

    public:
        form& form_;

        textbox& font_;
        button& font_setup_;

        combox& bgcolor_;
        button& bgcolor_setup_;

        combox& fgcolor_;
        button& fgcolor_setup_;

        textbox& sample_;

        button& apply_;
        button& cancel_;

    public:
        editor_setup_view(runa::widget_cfg& _cfg, nana::window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , font_{ wnd<textbox>("font.value") }
            , font_setup_{ wnd<button>("font.setup") }
            , bgcolor_{wnd<combox>("bgcolor.value")}
            , bgcolor_setup_{ wnd<button>("bgcolor.setup") }
            , fgcolor_{ wnd<combox>("fgcolor.value") }
            , fgcolor_setup_{ wnd<button>("fgcolor.setup") }
            , sample_{ wnd<textbox>("sample.value") }
            , apply_{ wnd<button>("cmd.apply") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
        }

    };

}

