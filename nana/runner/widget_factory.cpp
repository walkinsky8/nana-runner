// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/widget_factory.h>

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

#endif

