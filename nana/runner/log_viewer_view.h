// Created by walkinsky(lyh6188@hotmail.com), 2018/01/25
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::view {

    class LogViewer : public view_obj
    {
        widget_cfg& cfg_;

        textbox& content_;

        button& close_;
        button& exit_;

    public:
        static string type_name_() { return "log_viewer"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<LogViewer>(_cfg); }

    public:
        LogViewer(widget_cfg& _cfg)
            : cfg_{ _cfg }
            , content_{ _cfg.wnd<textbox>("content") }
            , close_{ _cfg.wnd<button>("cmd.close") }
            , exit_{ _cfg.wnd<button>("cmd.exit") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                content_.append(s, false);
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