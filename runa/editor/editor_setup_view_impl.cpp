/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#include "stdafx.h"

#include <runa/editor/editor_setup_view_impl.h>

using namespace runa::editor;
using namespace runa;

void editor_setup_view_impl::init()
{
    init_model();

    fn_update_ = std::bind(&self::update_model, this);

    on_focus(&font_, &model_().font_(), fn_update_);
    on_focus(&bgcolor_, &model_().colors_().bg_(), fn_update_);
    on_focus(&fgcolor_, &model_().colors_().fg_(), fn_update_);
    on_focus(&caption_, &model_().caption_(), fn_update_);

    on_selected(&bgcolor_, &model_().colors_().bg_(), fn_update_);
    on_selected(&fgcolor_, &model_().colors_().fg_(), fn_update_);

    font_setup_.events().click([&] { on_font_setup(font_, model_().font_()); });
    bgcolor_setup_.events().click([&] { on_color_setup(bgcolor_, model_().colors_().bg_()); });
    fgcolor_setup_.events().click([&] { on_color_setup(fgcolor_, model_().colors_().fg_()); });

    apply_.events().click([&] {
        //on_focus has updated model field
        //save_model();
        save_widget(target());
        });
    cancel_.events().click([&] { close(); });
}

void editor_setup_view_impl::on_font_setup(textbox& _w, font_model& _m)
{
    font_cntrl_.open(_w.caption(), [&](const font_model & _model) {
        _w << _model;
        _m = _model;
        update_model();
        });
}

void editor_setup_view_impl::on_color_setup(combox& _w, color_model& _m)
{
    color_cntrl_.open(_w.caption(), [&](const color_model& _model) {
        _w << _model;
        _m = _model;
        update_model();
    });
}

void editor_setup_view_impl::on_fini()
{
    font_cntrl_.close();
    color_cntrl_.close();
}

void editor_setup_view_impl::init_model()
{
    load_widget(caption_);
    load_model();
}

void editor_setup_view_impl::update_model()
{
    save_widget(caption_);
}

void editor_setup_view_impl::set_target(widget* _target)
{
    target_ = _target;
    load_widget(target());
    load_model();
    update_model();
}

void editor_setup_view_impl::load_widget(const widget& _w)
{
    model_().font_() = _w.typeface();
    model_().colors_().bg_() = _w.bgcolor();
    model_().colors_().fg_() = _w.fgcolor();
    model_().caption_() = _w.caption();
}

void editor_setup_view_impl::save_widget(widget& _w) const
{
    _w.typeface(model_().font_());
    _w.bgcolor(model_().colors_().bg_());
    _w.fgcolor(model_().colors_().fg_());
    _w.caption(model_().caption_());
}

void editor_setup_view_impl::load_model()
{
    font_ << model_().font_();
    bgcolor_ << model_().colors_().bg_();
    fgcolor_ << model_().colors_().fg_();
    caption_ << model_().caption_();
}

void editor_setup_view_impl::save_model()
{
    font_ >> model_().font_();
    bgcolor_ >> model_().colors_().bg_();
    fgcolor_ >> model_().colors_().fg_();
    caption_ >> model_().caption_();
}

