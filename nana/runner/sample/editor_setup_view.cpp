// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_setup_view.h>

using namespace nana::runner::sample;

void editor_setup_view::init()
{
    init_model();
    load_model();

    name_.events().text_changed([&] {
        name_ >> model_.font_().name_();
        save_model();
    });
    size_.events().text_changed([&] {
        size_ >> model_.font_().size_();
        slider_ << model_.font_().size_();
        save_model();
    });
    slider_.events().value_changed([&] {
        size_ << slider_.value();
    });
    bold_.events().checked([&] {
        bold_ >> model_.font_().bold_();
        save_model();
    });
    italic_.events().checked([&] {
        italic_ >> model_.font_().italic_();
        save_model();
    });
    strikeout_.events().checked([&] {
        strikeout_ >> model_.font_().strikeout_();
        save_model();
    });
    underline_.events().checked([&] {
        underline_ >> model_.font_().underline_();
        save_model();
    });

    bgcolor_.events().text_changed([&] {
        bgcolor_ >> model_.colors_().bg_();
        save_model();
    });
    fgcolor_.events().text_changed([&] {
        fgcolor_ >> model_.colors_().fg_();
        save_model();
    });

    cancel_.events().click([&] {
        close();
    });
}

void editor_setup_view::init_model()
{
    model_.font_() = sample_.typeface();
    model_.colors_().bg_() << sample_.bgcolor();
    model_.colors_().fg_() << sample_.fgcolor();
}

void editor_setup_view::load_model()
{
    name_ << model_.font_().name_();
    size_ << model_.font_().size_();
    slider_ << model_.font_().size_();
    bold_ << model_.font_().bold_();
    italic_ << model_.font_().italic_();
    strikeout_ << model_.font_().strikeout_();
    underline_ << model_.font_().underline_();
    bgcolor_ << model_.colors_().bg_();
    fgcolor_ << model_.colors_().fg_();
}

void editor_setup_view::save_model()
{
    sample_.typeface(model_.font_());
    sample_.bgcolor(get_color(model_.colors_().bg_()));
    sample_.fgcolor(get_color(model_.colors_().fg_()));
}
