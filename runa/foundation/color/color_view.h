// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/combox_cfg.h>
#include <runa/widgets/checkbox_cfg.h>
#include <runa/widgets/color_chooser_cfg.h>
#include <runa/widgets/label_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

    public:
        form& form_;

        combox& input_;
        button& input_update_;

        checkbox& chooser_type_rgb_;
        checkbox& chooser_type_hsl_;
        checkbox& chooser_type_hsv_;
        nana::radio_group chooser_type_helper_;

        color_chooser& chooser_value_;

        label& output_value_;
        label& output_rgb_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , input_{ wnd<combox>("input.value") }
            , input_update_{ wnd<button>("input.update") }
            , chooser_type_rgb_{ wnd<checkbox>("chooser.value.mode.RGB") }
            , chooser_type_hsl_{ wnd<checkbox>("chooser.value.mode.HSL") }
            , chooser_type_hsv_{ wnd<checkbox>("chooser.value.mode.HSV") }
            , chooser_value_{ wnd<color_chooser>("chooser.value.page") }
            , output_value_{ wnd<label>("output.value") }
            , output_rgb_{ wnd<label>("output.rgb") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            radio_group_init(chooser_type_helper_, { &chooser_type_rgb_, &chooser_type_hsl_, &chooser_type_hsv_ });
        }

    };

}

