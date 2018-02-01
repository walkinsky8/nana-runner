// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class Font : public view_obj
    {
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
        static pcstr type_name_() { return "font"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Font>(_cfg); }

    public:
        Font(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , name_{ _cfg.wnd<textbox>("name.value") }
            , size_{ _cfg.wnd<textbox>("size.value") }
            , slider_{ _cfg.wnd<slider>("size.slider") }
            , bold_{ _cfg.wnd<checkbox>("bold.value") }
            , italic_{ _cfg.wnd<checkbox>("italic.value") }
            , strikeout_{ _cfg.wnd<checkbox>("strikeout.value") }
            , underline_{ _cfg.wnd<checkbox>("underline.value") }
            , sample_{ _cfg.wnd<textbox>("sample.value") }
            , quit_{ _cfg.wnd<button>("close") }
        {
            name_ << sample_.typeface().name();
            size_ << sample_.typeface().size();

            name_.events().text_changed([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.strikeout(), f.underline()));
            });
            size_.events().text_changed([this] {
                font f = sample_.typeface();
                double sz = 0;
                size_ >> sz;
                sample_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.strikeout(), f.underline()));
            });
            slider_.events().value_changed([this] {
                size_ << slider_.value();
            });
            bold_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.strikeout(), f.underline()));
            });
            italic_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.strikeout(), f.underline()));
            });
            strikeout_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), strikeout_.checked(), f.underline()));
            });
            underline_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.strikeout(), underline_.checked()));
            });

            quit_.events().click([this] {
                cfg().close();
            });
        }

    };

}
