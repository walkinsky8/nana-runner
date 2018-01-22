// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::view {

    class Color : public view_obj
    {
        widget_cfg& cfg_;

        form& form_;

        textbox& bg_;
        textbox& fg_;

        textbox& sample_;

        button& quit_;

    public:
        static pcstr type_name_() { return "color"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Color>(_cfg); }

    public:
        Color(widget_cfg& _cfg)
            : cfg_{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , bg_{ _cfg.wnd<textbox>("bg.value") }
            , fg_{ _cfg.wnd<textbox>("fg.value") }
            , sample_{ _cfg.wnd<textbox>("sample.value") }
            , quit_{ _cfg.wnd<button>("quit") }
        {
            bg_ << sample_.bgcolor();
            fg_ << sample_.fgcolor();

            bg_.events().focus([this] {
                sample_.bgcolor(get_color(bg_.caption()));
            });
            fg_.events().focus([this] {
                sample_.fgcolor(get_color(fg_.caption()));
            });

            quit_.events().click([this] {
                form_.close();
            });
        }

    };

}
