// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <runa/base/object.h>

#include <runa/foundation/view_base.h>

#include <runa/foundation/view_factory.h>

#include <runa/foundation/model_base.h>

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
