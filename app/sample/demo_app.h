/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/15
#pragma once

#include <runa/foundation/app_base.h>

#include "demo_cntrl.h"

namespace runa { namespace sample {

    class demo_app : public app
    {
        demo_cntrl demo_;

    public:
        demo_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}}

