// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/panel_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/spinbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace runa::sample {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

    public:
        form& form_;

        combox& color_;

        panel& sample_;

        slider& r_;
        slider& g_;
        slider& b_;
        slider& h_;
        slider& s_;
        slider& l_;
        spinbox& r_v_;
        spinbox& g_v_;
        spinbox& b_v_;
        spinbox& h_v_;
        spinbox& s_v_;
        spinbox& l_v_;

        color_chooser& color_hsl_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , color_{ wnd<combox>("color.value") }
            , sample_{ wnd<panel>("sample.value") }
            , r_{ wnd<slider>("r.value") }
            , g_{ wnd<slider>("g.value") }
            , b_{ wnd<slider>("b.value") }
            , h_{ wnd<slider>("h.value") }
            , s_{ wnd<slider>("s.value") }
            , l_{ wnd<slider>("l.value") }
            , r_v_{ wnd<spinbox>("r.v") }
            , g_v_{ wnd<spinbox>("g.v") }
            , b_v_{ wnd<spinbox>("b.v") }
            , h_v_{ wnd<spinbox>("h.v") }
            , s_v_{ wnd<spinbox>("s.v") }
            , l_v_{ wnd<spinbox>("l.v") }
            , color_hsl_{ wnd<color_chooser>("hsl.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            color_ << sample_.bgcolor();

            color_.events().selected([&] { on_color_selected(); });
            color_.events().text_changed([&] { on_color_text_changed(); });

            r_.events().value_changed([&] { on_r_value_changed(); });
            g_.events().value_changed([&] { on_g_value_changed(); });
            b_.events().value_changed([&] { on_b_value_changed(); });

            h_.events().value_changed([&] { on_h_value_changed(); });
            s_.events().value_changed([&] { on_s_value_changed(); });
            l_.events().value_changed([&] { on_l_value_changed(); });

            r_v_.events().text_changed([&] { on_r_v_text_changed(); });
            g_v_.events().text_changed([&] { on_g_v_text_changed(); });
            b_v_.events().text_changed([&] { on_b_v_text_changed(); });

            h_v_.events().text_changed([&] { on_h_v_text_changed(); });
            s_v_.events().text_changed([&] { on_s_v_text_changed(); });
            l_v_.events().text_changed([&] { on_l_v_text_changed(); });

            color_hsl_.events().click([&](const nana::arg_click& _a) { on_hsl_click(_a); });
            color_hsl_.events().dbl_click([&](const nana::arg_mouse& _a) { on_hsl_dblclick(_a); });
            color_hsl_.events().mouse_enter([&](const nana::arg_mouse& _a) { on_hsl_mouse_event(_a); });
            color_hsl_.events().mouse_move([&](const nana::arg_mouse& _a) { on_hsl_mouse_event(_a); });
            color_hsl_.events().mouse_leave([&](const nana::arg_mouse& _a) { on_hsl_mouse_event(_a); });
            color_hsl_.events().mouse_down([&](const nana::arg_mouse& _a) { on_hsl_mouse_event(_a); });
            color_hsl_.events().mouse_up([&](const nana::arg_mouse& _a) { on_hsl_mouse_event(_a); });

            ok_.events().click([&] { on_ok(); });
            cancel_.events().click([&] { close(); });
        }

    private:
        void on_hsl_click(const nana::arg_click& _arg)
        {
            NAR_LOG_VAR(_arg);
        }

        void on_hsl_dblclick(const nana::arg_mouse& _arg)
        {
            NAR_LOG_VAR(_arg);
        }

        void on_hsl_mouse_event(const nana::arg_mouse& _arg)
        {
            NAR_LOG_VAR(_arg);
        }

        void on_color_text_changed()
        {
            NAR_LOG_VAR(color_);
            color c = get_color(color_.caption());
            sample_.bgcolor(c);
            r_ << c.r();
            g_ << c.g();
            b_ << c.b();
        }

        void on_color_selected()
        {
            NAR_LOG_VAR(color_);
            //color c = get_color(color_.caption());
            //sample_.bgcolor(c);
        }

        void rgb_changed()
        {
            color c{ r_.value(), g_.value(), b_.value() };
            NAR_LOG_VAR(c);
            color_ << c;
            //sample_.bgcolor(c);
        }

        void hsl_changed()
        {
            color c{};
            c.from_hsl(h_.value(), s_.value() / 100.0, l_.value() / 100.0);
            NAR_LOG_VAR(c);
            color_ << c;
            //sample_.bgcolor(c);
        }

        void on_r_value_changed()
        {
            NAR_LOG_VAR(r_.value());
            //rgb_changed();
            r_v_ << r_.value();
        }

        void on_g_value_changed()
        {
            NAR_LOG_VAR(g_.value());
            //rgb_changed();
            g_v_ << g_.value();
        }

        void on_b_value_changed()
        {
            NAR_LOG_VAR(b_.value());
            //rgb_changed();
            b_v_ << b_.value();
        }

        void on_h_value_changed()
        {
            NAR_LOG_VAR(h_.value());
            //hsl_changed();
            h_v_ << h_.value();
        }

        void on_s_value_changed()
        {
            NAR_LOG_VAR(s_.value());
            //hsl_changed();
            s_v_ << s_.value();
        }

        void on_l_value_changed()
        {
            NAR_LOG_VAR(l_.value());
            //hsl_changed();
            l_v_ << l_.value();
        }

        void on_r_v_text_changed()
        {
            NAR_LOG_VAR(r_v_);
            unsigned v = r_.value();
            r_v_ >> v;
            r_.value(v);
            rgb_changed();
        }

        void on_g_v_text_changed()
        {
            NAR_LOG_VAR(g_v_);
            unsigned v = g_.value();
            g_v_ >> v;
            g_.value(v);
            rgb_changed();
        }

        void on_b_v_text_changed()
        {
            NAR_LOG_VAR(b_v_);
            unsigned v = b_.value();
            b_v_ >> v;
            b_.value(v);
            rgb_changed();
        }

        void on_h_v_text_changed()
        {
            NAR_LOG_VAR(h_v_);
            unsigned v = h_.value();
            h_v_ >> v;
            h_.value(v);
            hsl_changed();
        }

        void on_s_v_text_changed()
        {
            NAR_LOG_VAR(s_v_);
            unsigned v = s_.value();
            s_v_ >> v;
            s_.value(v);
            hsl_changed();
        }

        void on_l_v_text_changed()
        {
            NAR_LOG_VAR(l_v_);
            unsigned v = l_.value();
            l_v_ >> v;
            l_.value(v);
            hsl_changed();
        }

        void on_ok()
        {
        }

    };

}

