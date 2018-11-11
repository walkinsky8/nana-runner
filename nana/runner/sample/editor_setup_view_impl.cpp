// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_setup_view_impl.h>

using namespace nana::runner::sample;
using namespace nana::runner;

void editor_setup_view_impl::init()
{
    init_model();

    name_.events().text_changed([&] {
        name_ >> model_().font_().name_();
        update_model();
    });
    size_.events().text_changed([&] {
        size_ >> model_().font_().size_();
        slider_ << model_().font_().size_();
        update_model();
    });
    slider_.events().value_changed([&] {
        size_ << slider_.value(); // will trigger event text_changed
    });
    bold_.events().checked([&] {
        bold_ >> model_().font_().bold_();
        update_model();
    });
    italic_.events().checked([&] {
        italic_ >> model_().font_().italic_();
        update_model();
    });
    strikeout_.events().checked([&] {
        strikeout_ >> model_().font_().strikeout_();
        update_model();
    });
    underline_.events().checked([&] {
        underline_ >> model_().font_().underline_();
        update_model();
    });

    bgcolor_.events().text_changed([&] {
        bgcolor_ >> model_().colors_().bg_();
        update_model();
    });
    fgcolor_.events().text_changed([&] {
        fgcolor_ >> model_().colors_().fg_();
        update_model();
    });

    apply_.events().click([&] {
        save_widget(target());
    });
    cancel_.events().click([&] {
        close();
    });
}

void editor_setup_view_impl::init_model()
{
    load_widget(sample_);
    load_model();
}

void editor_setup_view_impl::update_model()
{
    save_widget(sample_);
}

void editor_setup_view_impl::set_target(widget* _target)
{
    target_ = _target;
    load_widget(target());
    load_model();
    //save_widget(sample_);
}

void editor_setup_view_impl::load_widget(const widget& _w)
{
    model_().font_() << _w.typeface();
    model_().colors_().bg_() << _w.bgcolor();
    model_().colors_().fg_() << _w.fgcolor();
}

void editor_setup_view_impl::save_widget(widget& _w) const
{
    font f;
    model_().font_() >> f; _w.typeface(f);
    color c;
    model_().colors_().bg_() >> c; _w.bgcolor(c);
    model_().colors_().fg_() >> c; _w.fgcolor(c);
}

void editor_setup_view_impl::load_model()
{
    name_ << model_().font_().name_();
    size_ << model_().font_().size_();
    slider_ << model_().font_().size_();
    bold_ << model_().font_().bold_();
    italic_ << model_().font_().italic_();
    strikeout_ << model_().font_().strikeout_();
    underline_ << model_().font_().underline_();
    bgcolor_ << model_().colors_().bg_();
    fgcolor_ << model_().colors_().fg_();
}

void editor_setup_view_impl::save_model()
{
    name_ >> model_().font_().name_();
    size_ >> model_().font_().size_();
    //slider_ >> model_().font_().size_();
    bold_ >> model_().font_().bold_();
    italic_ >> model_().font_().italic_();
    strikeout_ >> model_().font_().strikeout_();
    underline_ >> model_().font_().underline_();
    bgcolor_ >> model_().colors_().bg_();
    fgcolor_ >> model_().colors_().fg_();
}

