// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/categorize_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class Demo : public view_obj
    {
        form& form_;

        categorize& categorize_;

        label& label_;
        combox& align_;
        combox& align_v_;
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

        textbox& text_;
        checkbox& editable_;
        checkbox& linewrap_;
        checkbox& multilines_;

        button& quit_;

        align m_label_align{ nana::align::left };
        align_v m_label_align_v{ nana::align_v::top };

    public:
        static pcstr type_name_() { return "demo"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Demo>(_cfg); }

    public:
        Demo(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ wnd<form>() }
            , categorize_{ wnd<categorize>("categorize") }
            , label_{ wnd<label>("label.value") }
            , align_{ wnd<combox>("label.align") }
            , align_v_{ wnd<combox>("label.align_v") }
            , bg_{ wnd<textbox>("color.bg.value") }
            , fg_{ wnd<textbox>("color.fg.value") }
            , name_{ wnd<textbox>("f.name.value") }
            , size_{ wnd<textbox>("f.size.value") }
            , bold_{ wnd<checkbox>("font.bold") }
            , italic_{ wnd<checkbox>("font.italic") }
            , strikeout_{ wnd<checkbox>("font.strikeout") }
            , underline_{ wnd<checkbox>("font.underline") }
            , text_{ wnd<textbox>("text") }
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

            label_.text_align(m_label_align.value(), m_label_align_v.value());
            align_ << m_label_align;
            align_v_ << m_label_align_v;
            align_.events().selected([this] {
                align_ >> m_label_align;
                label_.text_align(m_label_align.value(), m_label_align_v.value());
            });
            align_v_.events().selected([this] {
                align_v_ >> m_label_align_v;
                label_.text_align(m_label_align.value(), m_label_align_v.value());
            });

            bg_ << label_.bgcolor();
            fg_ << label_.fgcolor();
            bg_.events().focus([this] {
                label_.bgcolor(get_color(bg_.caption()));
            });
            fg_.events().focus([this] {
                label_.fgcolor(get_color(fg_.caption()));
            });

            auto tf = label_.typeface();
            name_ << tf.name();
            size_ << tf.size();
            bold_ << tf.bold();
            italic_ << tf.italic();
            strikeout_ << tf.strikeout();
            underline_ << tf.underline();
            name_.events().text_changed([this] {
                font f = label_.typeface();
                label_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            size_.events().text_changed([this] {
                font f = label_.typeface();
                double sz = 0;
                size_ >> sz;
                label_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            bold_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.underline(), f.strikeout()));
            });
            italic_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.underline(), f.strikeout()));
            });
            strikeout_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.underline(), strikeout_.checked()));
            });
            underline_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), underline_.checked(), f.strikeout()));
            });

            editable_.events().checked([this] {
                text_.editable(editable_.checked());
            });
            linewrap_.events().checked([this] {
                text_.line_wrapped(linewrap_.checked());
            });
            multilines_.events().checked([this] {
                text_.multi_lines(multilines_.checked());
            });

            quit_.events().click([this] {
                close();
            });
        }

    };

}
