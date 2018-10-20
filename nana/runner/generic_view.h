// Created by walkinsky(lyh6188@hotmail.com), 2018/10/12
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>

namespace nana::runner::view {

    class Generic : public view_obj
    {
    public:
        static pcstr type_name_() { return "generic"; }
        static view_ptr new_(widget_cfg& _cfg, window _parent) { return std::make_shared<Generic>(_cfg, _parent); }

    public:
        Generic(widget_cfg& _cfg, window _parent)
            : view_obj{ _cfg, _parent }
        {
        }

    private:

    };

}
