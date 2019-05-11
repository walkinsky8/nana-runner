/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/02/12
#pragma once

#include <runa/foundation/app_base.h>

#include "login_cntrl.h"
#include "editor_cntrl.h"

namespace runa { namespace editor {

    class editor_app : public app
    {
        login_cntrl login_;
        editor_cntrl editor_;

        bool nologin_{ false };
        bool nologwin_{ false };

    public:
        editor_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}}

