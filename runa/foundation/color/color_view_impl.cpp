// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#include "stdafx.h"

#include <runa/foundation/color/color_view_impl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

void color_view_impl::init()
{
    input_.events().selected([&] { on_color_selected(); });
    input_.events().text_changed([&] { on_color_text_changed(); });

    chooser_bar_.events().selected([&] { on_chooser_tab_changed(); });
    chooser_rgb_.events().value_changed([&](const arg_color_chooser& _arg) { on_chooser_value_changed(_arg.value); });
    chooser_hsl_.events().value_changed([&](const arg_color_chooser& _arg) { on_chooser_value_changed(_arg.value); });
    chooser_hsv_.events().value_changed([&](const arg_color_chooser& _arg) { on_chooser_value_changed(_arg.value); });

    ok_.events().click([&] { on_ok(); });
    cancel_.events().click([&] { on_cancel(); });

    set_model_proxy({});
}

void color_view_impl::set_model_proxy(model_proxy<color_model> const& _proxy)
{
    proxy_ = _proxy;

    load_model();

    color c = get_color(proxy_.data_.value_());
    input_ << c;
    update_color(c);
}

void color_view_impl::on_ok()
{
    save_model();
    NAR_LOG_VAR(proxy_.data_);

    proxy_();

    close();
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
    color c = get_color(input_.caption(), get_color_value());
    set_color_value(c);
}

void color_view_impl::on_chooser_tab_changed()
{
    // see color.nar: 0=rgb, 1=hsl, 2=hsv
    color_chooser_type type = get_chooser_type();
}

void color_view_impl::on_chooser_value_changed(const color& _color)
{
    NAR_LOG_VAR(_color);
    update_color(_color);
}

void color_view_impl::load_model()
{
    switch (get_chooser_type())
    {
    case color_chooser_type::rgb:
        chooser_rgb_ << proxy_.data_.value_();
        break;
    case color_chooser_type::hsl:
        chooser_hsl_ << proxy_.data_.value_();
        break;
    case color_chooser_type::hsv:
        chooser_hsv_ << proxy_.data_.value_();
        break;
    }
}

void color_view_impl::save_model()
{
    switch (get_chooser_type())
    {
    case color_chooser_type::rgb:
        chooser_rgb_ >> proxy_.data_.value_();
        break;
    case color_chooser_type::hsl:
        chooser_hsl_ >> proxy_.data_.value_();
        break;
    case color_chooser_type::hsv:
        chooser_hsv_ >> proxy_.data_.value_();
        break;
    }
}

color color_view_impl::get_color_value() const
{
    switch (get_chooser_type())
    {
    case color_chooser_type::rgb:
        return chooser_rgb_.value();
    case color_chooser_type::hsl:
        return chooser_hsl_.value();
    case color_chooser_type::hsv:
        return chooser_hsv_.value();
    }
    return {};
}

void color_view_impl::set_color_value(const color& _c)
{
    switch (get_chooser_type())
    {
    case color_chooser_type::rgb:
        chooser_rgb_.value(_c);
        break;
    case color_chooser_type::hsl:
        chooser_hsl_.value(_c);
        break;
    case color_chooser_type::hsv:
        chooser_hsv_.value(_c);
        break;
    }
}

color_chooser_type color_view_impl::get_chooser_type() const
{
    return static_cast<color_chooser_type>(chooser_bar_.selected());
}

void color_view_impl::update_color(const color& c)
{
    string s;
    s << "R=" << int(c.r() + 0.5);
    s << " G=" << int(c.g() + 0.5);
    s << " B=" << int(c.b() + 0.5);
    output_ << s;
    output_.bgcolor(c);
    output_.fgcolor(color_hsl{ c }.l() < 0.5 ? nana::colors::white : nana::colors::black);
}

