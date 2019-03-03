/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/01/22
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/font/font_view_impl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

void font_view_impl::init()
{
    model_.data_ << sample_.typeface();
    NAR_LOG_VAR(model_.data_);
    save_model();
    load_model();
    on_model_updated();

    name_.events().text_changed([this] { name_ >> model_.data_.name_(); on_model_updated(); });
    size_.events().text_changed([this] { size_ >> model_.data_.size_(); on_model_updated(); });
    slider_.events().value_changed([this] { size_ << slider_.value(); });
    bold_.events().checked([this] { bold_ >> model_.data_.bold_(); on_model_updated(); });
    italic_.events().checked([this] { italic_ >> model_.data_.italic_(); on_model_updated(); });
    underline_.events().checked([this] { underline_ >> model_.data_.underline_(); on_model_updated(); });
    strikeout_.events().checked([this] { strikeout_ >> model_.data_.strikeout_(); on_model_updated(); });

    ok_.events().click([&] { on_ok(); });
    cancel_.events().click([&] { on_cancel(); });
}

void font_view_impl::set_model_proxy(model_proxy<font_model> const& _proxy)
{
    NAR_LOG_VAR(_proxy.data_);
    model_ = _proxy;

    load_model();

    on_model_updated();
}

void font_view_impl::on_ok()
{
    save_model();
    NAR_LOG_VAR(model_.data_);

    model_();

    close();
}

void font_view_impl::on_cancel()
{
    NAR_LOG("cancel window");
    close();
}

void font_view_impl::load_model()
{
    NAR_LOG_DEBUG("value = " << model_.data_);
    name_ << model_.data_.name_();
    size_ << model_.data_.size_();
    slider_ << model_.data_.size_();
    bold_ << model_.data_.bold_();
    italic_ << model_.data_.italic_();
    underline_ << model_.data_.underline_();
    strikeout_ << model_.data_.strikeout_();
}

void font_view_impl::save_model()
{
    name_ >> model_.data_.name_();
    size_ >> model_.data_.size_();
    bold_ >> model_.data_.bold_();
    italic_ >> model_.data_.italic_();
    underline_ >> model_.data_.underline_();
    strikeout_ >> model_.data_.strikeout_();
    NAR_LOG_DEBUG("value = " << model_.data_);
}

void font_view_impl::on_model_updated()
{
    NAR_LOG_DEBUG(model_.data_);
    auto f = get_font_value();
    sample_.typeface(f);
    output_value_ << f;
}

font font_view_impl::get_font_value() const
{
    font f;
    model_.data_ >> f;
    return f;
}

#endif

