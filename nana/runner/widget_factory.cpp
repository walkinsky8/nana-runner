// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_factory.h>

nana::widget* nana::runner::create_widget(const string& _type, nana::window _parent_wnd, bool _visible)
{
    auto f = widget_factory::instance().get(_type);
    if (f)
        return f(_parent_wnd, _visible);
    return nullptr;
}

nana::runner::widget_factory::widget_factory()
{
    add("form",    [](nana::window _parent_wnd, bool _visible) { return new form(_parent_wnd); });
    add("label",   [](nana::window _parent_wnd, bool _visible) { return new label(_parent_wnd, _visible); });
    add("textbox", [](nana::window _parent_wnd, bool _visible) { return new textbox(_parent_wnd, _visible); });
    add("button",  [](nana::window _parent_wnd, bool _visible) { return new button(_parent_wnd, _visible); });
}

nana::runner::widget_factory & nana::runner::widget_factory::instance()
{
    static widget_factory __;
    return __;
}

void nana::runner::widget_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

nana::runner::create_func nana::runner::widget_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}
