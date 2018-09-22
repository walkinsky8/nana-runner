// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class logger : public view_obj
    {
    public:
        static string type_name_() { return "logger"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<logger>(_cfg); }

    public:
        form& form_;

        textbox& content_;

        button& close_;
        button& exit_;

    public:
        logger(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , content_{ _cfg.wnd<textbox>("content") }
            , close_{ _cfg.wnd<button>("cmd.close") }
            , exit_{ _cfg.wnd<button>("cmd.exit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                content_.append(s, false);
            });

            close_.events().click([this] { close(); });
            exit_.events().click([this] { close_all(); });
            form_.events().destroy([this] { close_all(); });
        }

    };

}
