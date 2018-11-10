// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample {

    class font_view : public view_obj
    {
        NAR_DEFINE_VIEW(font, view_obj);

    public:
        form& form_;

        textbox& name_;
        textbox& size_;
        slider& slider_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& strikeout_;
        checkbox& underline_;

        textbox& sample_;

        button& quit_;

    public:
        font_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , name_{ wnd<textbox>("name.value") }
            , size_{ wnd<textbox>("size.value") }
            , slider_{ wnd<slider>("size.slider") }
            , bold_{ wnd<checkbox>("bold.value") }
            , italic_{ wnd<checkbox>("italic.value") }
            , strikeout_{ wnd<checkbox>("strikeout.value") }
            , underline_{ wnd<checkbox>("underline.value") }
            , sample_{ wnd<textbox>("sample.value") }
            , quit_{ wnd<button>("close") }
        {
            name_ << sample_.typeface().name();
            size_ << sample_.typeface().size();

            name_.events().text_changed([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            size_.events().text_changed([this] {
                font f = sample_.typeface();
                double sz = 0;
                size_ >> sz;
                sample_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            slider_.events().value_changed([this] {
                size_ << slider_.value();
            });
            bold_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.underline(), f.strikeout()));
            });
            italic_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.underline(), f.strikeout()));
            });
            strikeout_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.underline(), strikeout_.checked()));
            });
            underline_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), underline_.checked(), f.strikeout()));
            });

            quit_.events().click([this] {
                close();
            });
        }

    };

}
