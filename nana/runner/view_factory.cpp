// Created by walkinsky(lyh6188@hotmail.com), 2018/01/21
#include "stdafx.h"

#include <nana/runner/view_factory.h>

nana::runner::view_factory::view_factory()
{
}

nana::runner::view_factory & nana::runner::view_factory::instance()
{
    static view_factory __;
    return __;
}

nana::runner::view_ptr nana::runner::view_factory::create(const string& _type, widget_cfg& _cfg, window _parent)
{
    auto f = instance().get(_type);
    if (f)
    {
        return f(_cfg, _parent);
    }
    return nullptr;
}

void nana::runner::view_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

nana::runner::view_factory::create_func nana::runner::view_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}
