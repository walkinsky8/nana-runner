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
        textbox& revert_;

        slider& r_;
        slider& g_;
        slider& b_;
        slider& h_;
        slider& s_;
        slider& l_;

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
            , revert_{ _cfg.wnd<textbox>("revert.value") }
            , r_{ _cfg.wnd<slider>("r.value") }
            , g_{ _cfg.wnd<slider>("g.value") }
            , b_{ _cfg.wnd<slider>("b.value") }
            , h_{ _cfg.wnd<slider>("h.value") }
            , s_{ _cfg.wnd<slider>("s.value") }
            , l_{ _cfg.wnd<slider>("l.value") }
            , quit_{ _cfg.wnd<button>("quit") }
        {
            bg_ << sample_.bgcolor();
            fg_ << sample_.fgcolor();

            bg_.events().focus([this] {
                color c = get_color(bg_.caption());
                sample_.bgcolor(c);
                revert_.fgcolor(c);
            });
            fg_.events().focus([this] {
                color c = get_color(fg_.caption());
                sample_.fgcolor(c);
                revert_.bgcolor(c);
            });

            r_.events().value_changed([this] {
                color c{ r_.value(), g_.value(), b_.value() };
                bg_ << c;
                sample_.bgcolor(c);
                revert_.fgcolor(c);
            });
            g_.events().value_changed([this] {
                color c{ r_.value(), g_.value(), b_.value() };
                bg_ << c;
                sample_.bgcolor(c);
                revert_.fgcolor(c);
            });
            b_.events().value_changed([this] {
                color c{ r_.value(), g_.value(), b_.value() };
                bg_ << c;
                sample_.bgcolor(c);
                revert_.fgcolor(c);
            });
            h_.events().value_changed([this] {
                color c{};
                c.from_hsl(h_.value(), s_.value()/1000.0, l_.value()/1000.0);
                fg_ << c;
                sample_.fgcolor(c);
                revert_.bgcolor(c);
            });
            s_.events().value_changed([this] {
                color c{};
                c.from_hsl(h_.value(), s_.value() / 1000.0, l_.value() / 1000.0);
                fg_ << c;
                sample_.fgcolor(c);
                revert_.bgcolor(c);
            });
            l_.events().value_changed([this] {
                color c{};
                c.from_hsl(h_.value(), s_.value() / 1000.0, l_.value() / 1000.0);
                fg_ << c;
                sample_.fgcolor(c);
                revert_.bgcolor(c);
            });

            quit_.events().click([this] {
                form_.close();
            });
        }

    };

}
