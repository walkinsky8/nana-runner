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
            checkbox& bold_;
            checkbox& italic_;
            checkbox& strikeout_;
            checkbox& underline_;

            textbox& log_;
            checkbox& editable_;
            checkbox& linewrap_;
            checkbox& multilines_;

            button& quit_;

        public:
            Hello(widget_cfg& _cfg, form& _form)
                : cfg_{ _cfg }, form_{ _form }
                , world_{ _cfg.wnd<label>("hello.world") }
                , bold_{ _cfg.wnd<checkbox>("hello.font.bold") }
                , italic_{ _cfg.wnd<checkbox>("hello.font.italic") }
                , strikeout_{ _cfg.wnd<checkbox>("hello.font.strikeout") }
                , underline_{ _cfg.wnd<checkbox>("hello.font.underline") }
                , log_{ _cfg.wnd<textbox>("hello.log") }
                , editable_{ _cfg.wnd<checkbox>("hello.cmd.editable") }
                , linewrap_{ _cfg.wnd<checkbox>("hello.cmd.linewrap") }
                , multilines_{ _cfg.wnd<checkbox>("hello.cmd.multilines") }
                , quit_{ _cfg.wnd<button>("hello.cmd.quit") }
            {
                set_log_handler([this](const string& s) {
                    write_console(s);
                    log_.append(s, false);
                });

                bold_.events().checked([this] {
                    font f = world_.typeface();
                    world_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.strikeout(), f.underline()));
                });
                italic_.events().checked([this] {
                    font f = world_.typeface();
                    world_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.strikeout(), f.underline()));
                });
                strikeout_.events().checked([this] {
                    font f = world_.typeface();
                    world_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), strikeout_.checked(), f.underline()));
                });
                underline_.events().checked([this] {
                    font f = world_.typeface();
                    world_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.strikeout(), underline_.checked()));
                });

                editable_.events().checked([this] {
                    log_.editable(editable_.checked());
                });
                linewrap_.events().checked([this] {
                    log_.line_wrapped(linewrap_.checked());
                });
                multilines_.events().checked([this] {
                    log_.multi_lines(multilines_.checked());
                });

                quit_.events().click([this] {
                    form_.close();
                });
            }

        };

    }

}
