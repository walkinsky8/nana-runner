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

        button& close_;
        button& exit_;

    public:
        static string type_name_() { return "hello"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Hello>(_cfg); }

    public:
        Hello(widget_cfg& _cfg)
            : cfg_{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , world_{ _cfg.wnd<label>("world") }
            , log_{ _cfg.wnd<textbox>("log") }
            , close_{ _cfg.wnd<button>("cmd.close") }
            , exit_{ _cfg.wnd<button>("cmd.exit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                log_.append(s, false);
            });

            close_.events().click([this] {
                cfg_.close();
            });
            exit_.events().click([this] {
                auto f = cfg_.close_all_();
                if (f)
                    f();
            });
        }

    };

}
