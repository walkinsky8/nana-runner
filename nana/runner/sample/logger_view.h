// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

#include <nana/runner/app_base.h>

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
            , form_{ wnd<form>() }
            , content_{ wnd<textbox>("content") }
            , close_{ wnd<button>("cmd.close") }
            , exit_{ wnd<button>("cmd.exit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                content_.append(s, false);
            });

            close_.events().click([this] {
                close();
            });
            exit_.events().click([] {
                app::close_all();
            });
            form_.events().destroy([] {
                app::close_all();
            });
        }

    };

}
