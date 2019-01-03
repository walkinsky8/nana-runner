// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#include "stdafx.h"

#include <runa/foundation/color/color_view_impl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

void color_view_impl::init()
{
    NAR_ENUM_ADD(color_mode, rgb, rgb);
    NAR_ENUM_ADD(color_mode, rgb, hsl);
    NAR_ENUM_ADD(color_mode, rgb, hsv);

    input_.events().selected([&] { on_color_selected(); });
    input_.events().text_changed([&] { on_color_text_changed(); });
    input_update_.events().click([&] { on_input_changed(); });

    chooser_type_.events().selected([&] { on_chooser_type_changed(); });
    chooser_value_.events().value_changed([&](const arg_color_chooser& _arg) { on_chooser_value_changed(_arg.value); });

    ok_.events().click([&] { on_ok(); });
    cancel_.events().click([&] { on_cancel(); });

    set_model_proxy({});
}

void color_view_impl::set_model_proxy(model_proxy<color_model> const& _proxy)
{
    model_ = _proxy;
    NAR_LOG_VAR(model_.data_);

    chooser_type_ << enum_color_mode() ;
    color c = model_.data_;
    input_ << c;
    load_model();
    update_output(c);
}

void color_view_impl::on_ok()
{
    save_model();
    NAR_LOG_VAR(model_.data_);

    model_();

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
    on_input_changed();
}

void color_view_impl::on_color_text_changed()
{
    NAR_LOG_VAR(input_);
}

void color_view_impl::on_input_changed()
{
    NAR_LOG_VAR(input_);
    color c = get_color(input_.caption(), get_value());
    model_.data_ = c;
    set_value(c);
}

void color_view_impl::on_chooser_type_changed()
{
    NAR_LOG_VAR(model_.data_);
    enum_color_mode mode;
    chooser_type_ >> mode;
    chooser_value_.mode(mode.value());
    input_ << get_string_value();
    set_value(model_.data_);
}

void color_view_impl::on_chooser_value_changed(const color& _color)
{
    NAR_LOG_VAR(_color);
    input_ << get_string_value();
    model_.data_ = _color;
    update_output(_color);
}

void color_view_impl::load_model()
{
    NAR_LOG_VAR(model_.data_);
    set_value(model_.data_);
}

void color_view_impl::save_model()
{
    model_.data_ = get_value();
    NAR_LOG_VAR(model_.data_);
}

string color_view_impl::get_string_value() const
{
    return chooser_value_.to_string();
}

color color_view_impl::get_value() const
{
    return chooser_value_.to_color();
}

void color_view_impl::set_value(const color& _new)
{
    chooser_value_.from_color(_new);
}

color_mode color_view_impl::get_chooser_type() const
{
    return static_cast<color_mode>(chooser_type_.option());
}

void color_view_impl::update_output(const color& c)
{
    std::ostringstream s;
    s << "#" << std::setfill('0') << std::setbase(16);
    s << std::setw(2) << int(c.r() + 0.5);
    s << std::setw(2) << int(c.g() + 0.5);
    s << std::setw(2) << int(c.b() + 0.5);
    output_ << to_upper(s.str());
    //output_.bgcolor(c);
}

