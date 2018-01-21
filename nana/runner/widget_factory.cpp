// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_factory.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/panel_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/categorize_cfg.h>

void nana::runner::init_widgets()
{
    add_widget<form_cfg>();
    add_widget<panel_cfg>();
    add_widget<label_cfg>();
    add_widget<textbox_cfg>();
    add_widget<button_cfg>();
    add_widget<checkbox_cfg>();
    add_widget<categorize_cfg>();
}

nana::runner::widget_factory::widget_factory()
{
}

nana::runner::widget_factory & nana::runner::widget_factory::instance()
{
    static widget_factory __;
    return __;
}

nana::runner::cfg_ptr nana::runner::widget_factory::create(const string& _type)
{
    auto f = instance().get(_type);
    if (f)
    {
        return f();
    }
    return nullptr;
}

void nana::runner::widget_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

nana::runner::widget_factory::create_func nana::runner::widget_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}
