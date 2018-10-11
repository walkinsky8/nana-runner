// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/categorize_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class Demo : public view_obj
    {
        form& form_;

        categorize& categorize_;

        label& world_;
        //color
        textbox& bg_;
        textbox& fg_;
        //font
        textbox& name_;
        textbox& size_;
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
        static pcstr type_name_() { return "demo"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Demo>(_cfg); }

    public:
        Demo(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ wnd<form>() }
            , categorize_{ wnd<categorize>("categorize") }
            , world_{ wnd<label>("world") }
            , bg_{ wnd<textbox>("color.bg.value") }
            , fg_{ wnd<textbox>("color.fg.value") }
            , name_{ wnd<textbox>("f.name.value") }
            , size_{ wnd<textbox>("f.size.value") }
            , bold_{ wnd<checkbox>("font.bold") }
            , italic_{ wnd<checkbox>("font.italic") }
            , strikeout_{ wnd<checkbox>("font.strikeout") }
            , underline_{ wnd<checkbox>("font.underline") }
            , log_{ wnd<textbox>("log") }
            , editable_{ wnd<checkbox>("cmd.editable") }
            , linewrap_{ wnd<checkbox>("cmd.linewrap") }
            , multilines_{ wnd<checkbox>("cmd.multilines") }
            , quit_{ wnd<button>("cmd.close") }
        {
            //set_log_handler([this](const string& s) {
            //    write_console(s);
            //    log_.append(s, false);
            //});

            //categorize_.caption(fs_ext::path_user());
            categorize_.caption(fs::current_path());

            bg_ << world_.bgcolor();
            fg_ << world_.fgcolor();
            name_ << world_.typeface().name();
            size_ << world_.typeface().size();

            bg_.events().focus([this] {
                world_.bgcolor(get_color(bg_.caption()));
            });
            fg_.events().focus([this] {
                world_.fgcolor(get_color(fg_.caption()));
            });

            name_.events().text_changed([this] {
                font f = world_.typeface();
                world_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            size_.events().text_changed([this] {
                font f = world_.typeface();
                double sz = 0;
                size_ >> sz;
                world_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            bold_.events().checked([this] {
                font f = world_.typeface();
                world_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.underline(), f.strikeout()));
            });
            italic_.events().checked([this] {
                font f = world_.typeface();
                world_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.underline(), f.strikeout()));
            });
            strikeout_.events().checked([this] {
                font f = world_.typeface();
                world_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.underline(), strikeout_.checked()));
            });
            underline_.events().checked([this] {
                font f = world_.typeface();
                world_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), underline_.checked(), f.strikeout()));
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
