// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/color_hsl_chooser_cfg.h>
#include <nana/runner/color_hsv_chooser_cfg.h>
#include <nana/runner/color_rgb_chooser_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

namespace runa::sample {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

        using chooser_type = color_rgb_chooser;
        using color_type = chooser_type::value_type;

    public:
        form& form_;

        combox& input_;

        chooser_type& chooser_;

        label& output_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , input_{ wnd<combox>("input.value") }
            , chooser_{ wnd<chooser_type>("chooser.value") }
            , output_{ wnd<label>("output.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            input_.events().selected([&] { on_color_selected(); });
            input_.events().text_changed([&] { on_color_text_changed(); });

            chooser_.events().value_changed([&] { on_chooser_value_changed(); });

            ok_.events().click([&] { on_ok(); });
            cancel_.events().click([&] { close(); });

            input_ << output_.bgcolor();
        }

    private:
        void on_ok()
        {
            NAR_LOG_VAR(chooser_.value());
        }

        void on_color_selected()
        {
            NAR_LOG_VAR(input_);
        }

        void on_color_text_changed()
        {
            NAR_LOG_VAR(input_);
            chooser_.value(color_type(get_color(input_.caption(), chooser_.value().to_color())));
        }

        void on_chooser_value_changed()
        {
            NAR_LOG_VAR(chooser_.value());
            update_color(chooser_.value());
        }

        void update_color(const color_type& _c)
        {
            nana::color c = _c.to_color();
            string s;
            s << "R=" << int(c.r() + 0.5);
            s << " G=" << int(c.g() + 0.5);
            s << " B=" << int(c.b() + 0.5);
            output_ << s;
            output_.bgcolor(c);
            output_.fgcolor(color_hsl{ c }.l() < 0.5 ? nana::colors::white : nana::colors::black);
        }

    };

}

