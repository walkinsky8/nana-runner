// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/combox_cfg.h>
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
        }

    };

}
