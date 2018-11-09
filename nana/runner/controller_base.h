// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/object.h>

#include <nana/runner/view_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/model_base.h>

namespace nana::runner
{
    class controller_obj;
    using cntrl_ptr = ptr<controller_obj>;

    class controller_obj : public object
    {
    public:
        controller_obj();

        // child class may implement it to add_view<>.
        // static void initialize()

        virtual void on_init() = 0;

        virtual void on_fini() = 0;

    };

}
