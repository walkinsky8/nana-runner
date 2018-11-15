// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_setup_view_impl.h>

using namespace nana::runner::sample;
using namespace nana::runner;

void editor_setup_view_impl::init()
{
    init_model();

    fn_update_ = std::bind(&self::update_model, this);

    on_text_changed(&name_, &model_().font_().name_(), fn_update_);
    on_text_changed(&size_, &model_().font_().size_(), fn_update_);
    on_text_changed(&size_, &model_().font_().size_(), [&] {slider_ << model_().font_().size_(); });
    //on_value_changed(&slider_, &model_().font_().size_(), fn_update_);
    on_value_changed(&slider_, &model_().font_().size_(), [&] {size_ << model_().font_().size_(); });
    on_checked(&bold_, &model_().font_().bold_(), fn_update_);
    on_checked(&italic_, &model_().font_().italic_(), fn_update_);
    on_checked(&strikeout_, &model_().font_().strikeout_(), fn_update_);
    on_checked(&underline_, &model_().font_().underline_(), fn_update_);
    on_text_changed(&bgcolor_, &model_().colors_().bg_(), fn_update_);
    on_text_changed(&fgcolor_, &model_().colors_().fg_(), fn_update_);

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

