/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/widget_factory.h>

runa::widget_factory::widget_factory()
{
}

runa::widget_factory & runa::widget_factory::instance()
{
    static widget_factory __;
    return __;
}

runa::cfg_ptr runa::widget_factory::create(const string& _type)
{
    auto f = instance().get(_type);
    if (f)
    {
        return f();
    }
    return nullptr;
}

void runa::widget_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

runa::widget_factory::create_func runa::widget_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}

#endif

