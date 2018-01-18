// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    namespace view {

        class Hello
        {
            widget_cfg& cfg_;
            form& form_;

            label& world_;
            textbox& log_;
            button& quit_;

        public:
            Hello(widget_cfg& _cfg, form& _form)
                : cfg_{ _cfg }, form_{ _form }
                , world_{ _cfg.wnd<label>("hello.world") }
                , log_{ _cfg.wnd<textbox>("hello.log") }
                , quit_{ _cfg.wnd<button>("hello.cmd.quit") }
            {
                set_log_handler([this](const string& s) {
                    write_console(s);
                    log_.append(s, false);
                });

                quit_.events().click([this] {
                    form_.close();
                });
            }

        };

    }

}
