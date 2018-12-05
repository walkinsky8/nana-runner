// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/object.h>

#include <nana/runner/view_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/model_base.h>

namespace runa
{
    class controller_obj;
    using cntrl_ptr = ptr<controller_obj>;

    class controller_obj : public object
    {
    public:
        ~controller_obj();
        controller_obj();

    };

}
