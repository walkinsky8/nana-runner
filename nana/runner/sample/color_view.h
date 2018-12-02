// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/color_hsl_chooser_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

namespace runa::sample {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

    public:
        form& form_;

        combox& color_;

        color_hsl_chooser& color_hsl_;

        label& hsl_text_;
        label& rgb_text_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , color_{ wnd<combox>("color.value") }
            , color_hsl_{ wnd<color_hsl_chooser>("hsl.value") }
            , hsl_text_{ wnd<label>("hsl_text") }
            , rgb_text_{ wnd<label>("rgb_text") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            color_hsl_.events().value_changed([&] { on_hsl_value_changed(); });

            color_.events().selected([&] { on_color_selected(); });
            color_.events().text_changed([&] { on_color_text_changed(); });

            ok_.events().click([&] { on_ok(); });
            cancel_.events().click([&] { close(); });

            color_ << color_hsl_.value().to_color();
            update_color(color_hsl_.value());
        }

    private:
        void on_hsl_value_changed()
        {
            NAR_LOG_VAR(color_hsl_.value());
            update_color(color_hsl_.value());
        }

        void on_color_text_changed()
        {
            NAR_LOG_VAR(color_);
            color_hsl_.value(color_hsl(get_color(color_.caption(), color_hsl_.value().to_color())));
            update_color(color_hsl_.value());
        }

        void on_color_selected()
        {
            NAR_LOG_VAR(color_);
        }

        void on_ok()
        {
            NAR_LOG_VAR(color_hsl_.value());
        }

        void update_color(const color_hsl& _c)
        {
            string s;
            s << "H=" << int(_c.h() + 0.5);
            s << " S=" << int(100 * (_c.s() + 0.005)) << "%";
            s << " L=" << int(100 * (_c.l() + 0.005)) << "%";
            hsl_text_ << s;
            s.clear();
            color c = _c.to_color();
            s << "R=" << int(c.r() + 0.5);
            s << " G=" << int(c.g() + 0.5);
            s << " B=" << int(c.b() + 0.5);
            rgb_text_ << s;
        }

    };

}

