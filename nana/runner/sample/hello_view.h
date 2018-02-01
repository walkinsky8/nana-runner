// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class Hello : public view_obj
    {
        label& world_;

        textbox& text_;

        button& close_;

    public:
        static string type_name_() { return "hello"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Hello>(_cfg); }

    public:
        Hello(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , world_{ _cfg.wnd<label>("world") }
            , text_{ _cfg.wnd<textbox>("text") }
            , close_{ _cfg.wnd<button>("close") }
        {
            close_.events().click([this] { close(); });
        }

    };

}
