// Created by walkinsky(lyh6188@hotmail.com), 2018/10/12
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>

namespace nana::runner::view {

    class Generic : public view_obj
    {
    public:
        static pcstr type_name_() { return "generic"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Generic>(_cfg); }

    public:
        Generic(widget_cfg& _cfg)
            : view_obj{ _cfg }
        {
        }

    private:

    };

}
