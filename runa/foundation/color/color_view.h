// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/combox_cfg.h>
#include <runa/widgets/tabbar_cfg.h>
#include <runa/widgets/color_hsl_chooser_cfg.h>
#include <runa/widgets/color_hsv_chooser_cfg.h>
#include <runa/widgets/color_rgb_chooser_cfg.h>
#include <runa/widgets/label_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa {

    class color_view : public view_obj
    {
        NAR_DEFINE_VIEW(color, view_obj);

    public:
        form& form_;

        combox& input_;

        tabbar_lite& chooser_bar_;
        color_rgb_chooser& chooser_rgb_;
        color_hsl_chooser& chooser_hsl_;
        color_hsv_chooser& chooser_hsv_;

        label& output_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , input_{ wnd<combox>("input.value") }
            , chooser_bar_{ wnd<tabbar_lite>("chooser.value.bar") }
            , chooser_rgb_{ child_view("chooser.value.bar.RGB")->wnd<color_rgb_chooser>("rgb") }
            , chooser_hsl_{ child_view("chooser.value.bar.HSL")->wnd<color_hsl_chooser>("hsl") }
            , chooser_hsv_{ child_view("chooser.value.bar.HSV")->wnd<color_hsv_chooser>("hsv") }
            , output_{ wnd<label>("output.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
        }

    };

}

