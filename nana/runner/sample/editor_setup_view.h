// Created by walkinsky(lyh6188@hotmail.com), 2018/02/11
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

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

        struct model {
            font_model font_;
            struct colors {
                string bg_;
                string fg_;
            } colors_;
        } model_;

    public:
        editor_setup_view(widget_cfg& _cfg, window _parent)
            : view_obj{ _cfg, _parent }
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
            init_model();
            load_model();

            name_.events().text_changed([&] {
                name_ >> model_.font_.name_;
                save_model();
            });
            size_.events().text_changed([&] {
                size_ >> model_.font_.size_;
                slider_ << model_.font_.size_;
                save_model();
            });
            slider_.events().value_changed([&] {
                size_ << slider_.value();
            });
            bold_.events().checked([&] {
                bold_ >> model_.font_.bold_;
                save_model();
            });
            italic_.events().checked([&] {
                italic_ >> model_.font_.italic_;
                save_model();
            });
            strikeout_.events().checked([&] {
                strikeout_ >> model_.font_.strikeout_;
                save_model();
            });
            underline_.events().checked([&] {
                underline_ >> model_.font_.underline_;
                save_model();
            });

            bgcolor_.events().text_changed([&] {
                bgcolor_ >> model_.colors_.bg_;
                save_model();
            });
            fgcolor_.events().text_changed([&] {
                fgcolor_ >> model_.colors_.fg_;
                save_model();
            });

            cancel_.events().click([&] {
                close();
            });
        }


        void init_model()
        {
            model_.font_ = sample_.typeface();
            model_.colors_.bg_ << sample_.bgcolor();
            model_.colors_.fg_ << sample_.fgcolor();
        }

        void load_model()
        {
            name_ << model_.font_.name_;
            size_ << model_.font_.size_;
            slider_ << model_.font_.size_;
            bold_ << model_.font_.bold_;
            italic_ << model_.font_.italic_;
            strikeout_<< model_.font_.strikeout_;
            underline_ << model_.font_.underline_;
            bgcolor_ << model_.colors_.bg_;
            fgcolor_ << model_.colors_.fg_;
        }

        void save_model()
        {
            sample_.typeface(model_.font_);
            sample_.bgcolor(get_color(model_.colors_.bg_));
            sample_.fgcolor(get_color(model_.colors_.fg_));
        }

    };

}
