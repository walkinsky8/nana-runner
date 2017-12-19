// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    class form_cfg : public widget_cfg
    {
        using super = widget_cfg;

    public:
        void init_widget(widget& _w) const override;

    };

}
