// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>
#include <runa/widgets/combox_cfg.h>
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

        combox& chooser_type_;
        color_chooser& chooser_value_;

        label& output_;

        button& ok_;
        button& cancel_;

    public:
        color_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , input_{ wnd<combox>("input.value") }
            , input_update_{ wnd<button>("input.update") }
            , chooser_type_{ wnd<combox>("chooser.value.mode") }
            , chooser_value_{ wnd<color_chooser>("chooser.value.page") }
            , output_{ wnd<label>("output.value") }
            , ok_{ wnd<button>("cmd.OK") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
        }

    };

}

