/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/12
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>

namespace runa {

    class generic_view : public view_obj
    {
        NAR_DEFINE_VIEW(generic, view_obj);

    public:
        generic_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
        }

    private:

    };

}
