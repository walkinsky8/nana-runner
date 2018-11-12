// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample {

    class logger_view : public view_obj
    {
        NAR_DEFINE_VIEW(logger, view_obj);

    public:
        form& form_;

        textbox& content_;

        checkbox& wordwrap_;
        button& close_;
        button& exit_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , content_{ wnd<textbox>("content") }
            , wordwrap_{ wnd<checkbox>("cmd.wordwrap") }
            , close_{ wnd<button>("cmd.close") }
            , exit_{ wnd<button>("cmd.exit") }
        {
        }

    };

}

