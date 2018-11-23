// Created by walkinsky(lyh6188@hotmail.com), 2018/02/11
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/spinbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace runa::sample {

    class editor_setup_view : public view_obj
    {
        NAR_DEFINE_VIEW(editor_setup, view_obj);

    public:
        form& form_;

        textbox& name_;
        spinbox& size_;
        slider& slider_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& strikeout_;
        checkbox& underline_;

        combox& bgcolor_;
        combox& fgcolor_;

        textbox& sample_;

        button& apply_;
        button& cancel_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , name_{ wnd<textbox>("name.value") }
            , size_{ wnd<spinbox>("size.value") }
            , slider_{ wnd<slider>("size.slider") }
            , bold_{ wnd<checkbox>("bold.value") }
            , italic_{ wnd<checkbox>("italic.value") }
            , strikeout_{ wnd<checkbox>("strikeout.value") }
            , underline_{ wnd<checkbox>("underline.value") }
            , bgcolor_{wnd<combox>("bgcolor.value")}
            , fgcolor_{ wnd<combox>("fgcolor.value") }
            , sample_{ wnd<textbox>("sample.value") }
            , apply_{ wnd<button>("cmd.apply") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
        }

    };

}

