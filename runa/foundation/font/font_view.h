/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/22
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/textbox_cfg.h>
#include <runa/widgets/spinbox_cfg.h>
#include <runa/widgets/slider_cfg.h>
#include <runa/widgets/checkbox_cfg.h>
#include <runa/widgets/label_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa {

    class font_view : public view_obj
    {
        NAR_DEFINE_VIEW(font, view_obj);

    public:
        form& form_;

        textbox& name_;
        spinbox& size_;
        slider& slider_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& underline_;
        checkbox& strikeout_;

        textbox& sample_;

        label& output_value_;

        button& ok_;
        button& cancel_;

    public:
        font_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , name_{ wnd<textbox>("name.value") }
            , size_{ wnd<spinbox>("size.value") }
            , slider_{ wnd<slider>("size.slider") }
            , bold_{ wnd<checkbox>("style.bold") }
            , italic_{ wnd<checkbox>("style.italic") }
            , underline_{ wnd<checkbox>("style.underline") }
            , strikeout_{ wnd<checkbox>("style.strikeout") }
            , sample_{ wnd<textbox>("sample") }
            , output_value_{ wnd<label>("output.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
        }

    };

}
