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
        textbox& r_v_;
        textbox& g_v_;
        textbox& b_v_;
        textbox& h_v_;
        textbox& s_v_;
        textbox& l_v_;

        button& quit_;

    public:
        static pcstr type_name_() { return "color"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Color>(_cfg); }

    public:
        Color(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , bg_{ _cfg.wnd<textbox>("bg.value") }
            , fg_{ _cfg.wnd<textbox>("fg.value") }
            , sample_{ _cfg.wnd<textbox>("sample.normal") }
            , revert_{ _cfg.wnd<textbox>("sample.revert") }
            , r_{ _cfg.wnd<slider>("r.value") }
            , g_{ _cfg.wnd<slider>("g.value") }
            , b_{ _cfg.wnd<slider>("b.value") }
            , h_{ _cfg.wnd<slider>("h.value") }
            , s_{ _cfg.wnd<slider>("s.value") }
            , l_{ _cfg.wnd<slider>("l.value") }
            , r_v_{ _cfg.wnd<textbox>("r.v") }
            , g_v_{ _cfg.wnd<textbox>("g.v") }
            , b_v_{ _cfg.wnd<textbox>("b.v") }
            , h_v_{ _cfg.wnd<textbox>("h.v") }
            , s_v_{ _cfg.wnd<textbox>("s.v") }
            , l_v_{ _cfg.wnd<textbox>("l.v") }
            , quit_{ _cfg.wnd<button>("close") }
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
                on_rgb_changed();
                r_v_ << r_.value();
            });
            g_.events().value_changed([this] {
                on_rgb_changed();
                g_v_ << g_.value();
            });
            b_.events().value_changed([this] {
                on_rgb_changed();
                b_v_ << b_.value();
            });
            h_.events().value_changed([this] {
                on_hsl_changed();
                h_v_ << h_.value();
            });
            s_.events().value_changed([this] {
                on_hsl_changed();
                s_v_ << s_.value();
            });
            l_.events().value_changed([this] {
                on_hsl_changed();
                l_v_ << l_.value();
            });

            r_v_.events().focus([this] {
                unsigned v = r_.value();
                r_v_ >> v;
                r_.value(v);
                on_rgb_changed();
            });
            g_v_.events().focus([this] {
                unsigned v = g_.value();
                g_v_ >> v;
                g_.value(v);
                on_rgb_changed();
            });
            b_v_.events().focus([this] {
                unsigned v = b_.value();
                b_v_ >> v;
                b_.value(v);
                on_rgb_changed();
            });
            h_v_.events().focus([this] {
                unsigned v = h_.value();
                h_v_ >> v;
                h_.value(v);
                on_hsl_changed();
            });
            s_v_.events().focus([this] {
                unsigned v = s_.value();
                s_v_ >> v;
                s_.value(v);
                on_hsl_changed();
            });
            l_v_.events().focus([this] {
                unsigned v = l_.value();
                l_v_ >> v;
                l_.value(v);
                on_hsl_changed();
            });

            quit_.events().click([this] {
                cfg().close();
            });
        }

    private:
        void on_rgb_changed()
        {
            color c{ r_.value(), g_.value(), b_.value() };
            bg_ << c;
            sample_.bgcolor(c);
            revert_.fgcolor(c);
        }

        void on_hsl_changed()
        {
            color c{};
            c.from_hsl(h_.value(), s_.value() / 256.0, l_.value() / 256.0);
            fg_ << c;
            sample_.fgcolor(c);
            revert_.bgcolor(c);
        }

    };

}
