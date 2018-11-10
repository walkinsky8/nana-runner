// Created by walkinsky(lyh6188@hotmail.com), 2018/02/11
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

#include <nana/runner/sample/editor_setup_model.h>

namespace nana::runner::sample {

    class editor_setup_view : public view_obj
    {
        NAR_DEFINE_VIEW(editor_setup, view_obj);

    public:
        form& form_;

        textbox& name_;
        textbox& size_;
        slider& slider_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& strikeout_;
        checkbox& underline_;

        textbox& bgcolor_;
        textbox& fgcolor_;

        textbox& sample_;

        button& apply_;
        button& ok_;
        button& cancel_;

        editor_setup_model model_;

    public:
        editor_setup_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , name_{ wnd<textbox>("name.value") }
            , size_{ wnd<textbox>("size.value") }
            , slider_{ wnd<slider>("size.slider") }
            , bold_{ wnd<checkbox>("bold.value") }
            , italic_{ wnd<checkbox>("italic.value") }
            , strikeout_{ wnd<checkbox>("strikeout.value") }
            , underline_{ wnd<checkbox>("underline.value") }
            , bgcolor_{wnd<textbox>("bgcolor.value")}
            , fgcolor_{ wnd<textbox>("fgcolor.value") }
            , sample_{ wnd<textbox>("sample.value") }
            , apply_{ wnd<button>("cmd.apply") }
            , ok_{ wnd<button>("cmd.ok") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            init();
        }

    private:
        void init();

        void init_model();

        void load_model();

        void save_model();

    };

}
