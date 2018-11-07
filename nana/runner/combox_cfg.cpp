// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#include "stdafx.h"

#include "combox_cfg.h"

#include "option_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::combox_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);

    size_t pos = 0;
    for (auto& i : children_())
    {
        if (i)
        {
            w.push_back(i->get_caption());
            auto& child = i->cast<option_cfg>();
            if (!child.image_().empty())
            {
                w.image(pos, app::create_image(child.image_()));
            }
        }
        ++pos;
    }

    if (!selected_().empty())
        w.option(selected_().value());
    if (!editable_().empty())
        w.editable(editable_().value());
}

void nana::runner::operator<<(combox& _w, const strings& _v)
{
    for (auto& i : _v)
        _w.push_back(i);
}

void nana::runner::operator>>(const combox& _w, strings& _v)
{
    for (size_t i = 0; i < _w.the_number_of_options(); ++i)
        _v.push_back(_w.text(i));
}

