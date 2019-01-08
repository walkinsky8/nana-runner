// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#include "stdafx.h"

#include <runa/foundation/color/color_view_impl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

void color_view_impl::init()
{
    input_.events().selected([&] { on_color_selected(); });
    input_.events().text_changed([&] { on_color_text_changed(); });
    input_update_.events().click([&] { on_input_changed(); });

    chooser_type_rgb_.events().checked([&] { if (chooser_type_rgb_.checked()) on_chooser_type_changed(); });
    chooser_type_hsl_.events().checked([&] { if (chooser_type_hsl_.checked()) on_chooser_type_changed(); });
    chooser_type_hsv_.events().checked([&] { if (chooser_type_hsv_.checked()) on_chooser_type_changed(); });
    chooser_value_.events().color_changed([&](const arg_color_chooser& _arg) { on_chooser_color_value_changed(); });

    ok_.events().click([&] { on_ok(); });
    cancel_.events().click([&] { on_cancel(); });

    set_model_proxy({});
}

void color_view_impl::set_model_proxy(model_proxy<color_model> const& _proxy)
{
    model_ = _proxy;
    NAR_LOG_VAR(model_.data_);

    if (_proxy.data_.empty())
        model_.data_ = get_string_value();

    color c = model_.data_;
    input_ << c;

    chooser_value_.mode(get_chooser_type());

    load_model();
    
    update_output();
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
    color c = get_color(input_.caption(), get_color_value());
    model_.data_ = c;
    set_color_value(c);
}

void color_view_impl::on_chooser_type_changed()
{
    NAR_LOG_VAR(model_.data_);
    chooser_value_.mode(get_chooser_type());
    load_model();
    //update_output();
}

void color_view_impl::on_chooser_color_value_changed()
{
    color color_value = get_color_value();
    NAR_LOG_VAR(color_value);
    model_.data_ = color_value;
    update_output();
}

void color_view_impl::load_model()
{
    NAR_LOG_VAR(model_.data_);
    set_color_value(model_.data_);
}

void color_view_impl::save_model()
{
    model_.data_ = get_color_value();
    NAR_LOG_VAR(model_.data_);
}

string color_view_impl::get_string_value() const
{
    auto value = chooser_value_.to_string();
    NAR_LOG_VAR(value);
    return value;
}

color color_view_impl::get_color_value() const
{
    color value = chooser_value_.to_color();
    NAR_LOG_VAR(value);
    return value;
}

void color_view_impl::set_color_value(const color& _value)
{
    NAR_LOG_VAR(_value);
    chooser_value_.from_color(_value);
}

color_mode color_view_impl::get_chooser_type() const
{
    int which = static_cast<int>(chooser_type_group_.checked());
    enum_color_mode mode = which < 0 ? chooser_value_.mode() : enum_color_mode{ which };
    NAR_LOG_VAR(mode);
    return mode.value();
}

void color_view_impl::update_output()
{
    output_value_ << get_string_value();
    //NAR_LOG_VAR(output_value_);

    color c = get_color_value();
    std::ostringstream s;
    s << "#" << std::setfill('0') << std::setbase(16);
    s << std::setw(2) << int(c.r() + 0.5);
    s << std::setw(2) << int(c.g() + 0.5);
    s << std::setw(2) << int(c.b() + 0.5);
    output_rgb_ << to_upper(s.str());
    //NAR_LOG_VAR(output_rgb_);
}

