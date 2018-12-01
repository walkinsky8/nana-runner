// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/panel_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/spinbox_cfg.h>
#include <nana/runner/color_chooser_cfg.h>
#include <nana/runner/button_cfg.h>

namespace runa::sample {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

    public:
        form& form_;

        color_chooser& color_hsl_;

        combox& color_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , color_hsl_{ wnd<color_chooser>("hsl.value") }
            , color_{ wnd<combox>("color.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            color_hsl_.events().value_changed([&] { on_hsl_value_changed(); });

            color_.events().selected([&] { on_color_selected(); });
            color_.events().text_changed([&] { on_color_text_changed(); });

            ok_.events().click([&] { on_ok(); });
            cancel_.events().click([&] { close(); });

            color_ << color_hsl_.value().to_color();
        }

    private:
        void on_hsl_value_changed()
        {
            NAR_LOG_VAR(color_hsl_.value());
            NAR_LOG_VAR(color_hsl_.value().to_color());
        }

        void on_color_text_changed()
        {
            NAR_LOG_VAR(color_);
            color_hsl_.value(color_hsl(get_color(color_.caption(), color_hsl_.value().to_color())));
        }

        void on_color_selected()
        {
            NAR_LOG_VAR(color_);
        }

        void on_ok()
        {
            NAR_LOG_VAR(color_hsl_.value());
        }

    };

}

