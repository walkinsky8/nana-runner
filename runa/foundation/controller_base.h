/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/01/15
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
