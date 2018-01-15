// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    class button_cfg : public widget_cfg
    {
    public:
        using super = widget_cfg;
        using self = button_cfg;
        using ui_type = nana::button;

        static pcstr type_name_() { return "button"; }
        string type_name() const override { return type_name_(); }

        static view_ptr new_() { return std::make_shared<self>(); }
        view_ptr new_obj() const override { return new_(); }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }
        wnd_ptr create_widget(window p, bool v) const override { return create_widget_(p, v); }

        void init_widget(widget& _w) const override;

    };

}
