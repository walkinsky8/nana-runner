// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#include "stdafx.h"

#include <nana/runner/color_view_impl.h>

#include <nana/runner/app_base.h>

using namespace runa;

void color_view_impl::init()
{
    input_.events().selected([&] { on_color_selected(); });
    input_.events().text_changed([&] { on_color_text_changed(); });

    chooser_.events().value_changed([&] { on_chooser_value_changed(); });

    ok_.events().click([&] { on_ok(); });
    cancel_.events().click([&] { on_cancel(); });
}

void color_view_impl::set_model_proxy(model_proxy<color_model> const& _proxy)
{
    proxy_ = _proxy;

    load_model();

    input_ << get_color(proxy_.data_.value_());
}

void color_view_impl::on_ok()
{
    save_model();
    NAR_LOG_VAR(proxy_.data_);

    proxy_();
}

void color_view_impl::on_cancel()
{
    NAR_LOG("cancel window");
    close();
}

void color_view_impl::on_color_selected()
{
    NAR_LOG_VAR(input_);
}

void color_view_impl::on_color_text_changed()
{
    NAR_LOG_VAR(input_);
    chooser_.value(color_type(get_color(input_.caption(), chooser_.value().to_color())));
}

void color_view_impl::on_chooser_value_changed()
{
    NAR_LOG_VAR(chooser_.value());
    update_color(chooser_.value());
}

void color_view_impl::load_model()
{
    chooser_ << proxy_.data_.value_();
}

void color_view_impl::save_model()
{
    chooser_ >> proxy_.data_.value_();
}

void color_view_impl::update_color(const color_type& _c)
{
    nana::color c = _c.to_color();
    string s;
    s << "R=" << int(c.r() + 0.5);
    s << " G=" << int(c.g() + 0.5);
    s << " B=" << int(c.b() + 0.5);
    output_ << s;
    output_.bgcolor(c);
    output_.fgcolor(color_hsl{ c }.l() < 0.5 ? nana::colors::white : nana::colors::black);
}

