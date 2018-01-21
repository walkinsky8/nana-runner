// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::view {

    class Hello : public view_obj
    {
        widget_cfg& cfg_;

        form& form_;

        label& world_;

        textbox& log_;

        button& quit_;

    public:
        static string type_name_() { return "hello"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Hello>(_cfg); }

    public:
        Hello(widget_cfg& _cfg)
            : cfg_{ _cfg }
            , form_{ _cfg.wnd<form>("hello") }
            , world_{ _cfg.wnd<label>("hello.world") }
            , log_{ _cfg.wnd<textbox>("hello.log") }
            , quit_{ _cfg.wnd<button>("hello.quit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                log_.append(s, false);
            });

            quit_.events().click([this] {
                form_.close();
            });
        }

        void show() override { form_.show(); }

    };

}
