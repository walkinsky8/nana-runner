/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/11/10
#pragma once

#include <runa/foundation/view_base.h>

namespace runa { namespace sample {

    class hello_view : public view_obj
    {
        NAR_DEFINE_VIEW(hello, view_obj);

    public:
        hello_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
        }

    };

}}
