/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/03/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/font/font_cntrl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

font_cntrl::font_cntrl()
{
    add_view<font_view_impl>();
}

font_cntrl::~font_cntrl()
{
    close();
}

void font_cntrl::open(const model_type& _input, model_type::on_result _on_result)
{
    model_ = { _input, _on_result };

    auto& vi = app::show_view<font_view_impl>(view_);
    vi.set_model_proxy(model_);
}

void font_cntrl::close()
{
    close_view(view_);
}

#endif

