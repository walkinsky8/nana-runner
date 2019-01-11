/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/01/21
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/view_factory.h>

runa::view_factory::view_factory()
{
}

runa::view_factory & runa::view_factory::instance()
{
    static view_factory __;
    return __;
}

runa::view_ptr runa::view_factory::create(const string& _type, widget_cfg& _cfg, window _parent)
{
    auto f = instance().get(_type);
    if (f)
    {
        return f(_cfg, _parent);
    }
    return nullptr;
}

void runa::view_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

runa::view_factory::create_func runa::view_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}

#endif

