/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/12/04
#include "stdafx.h"

#include <runa/foundation/color/color_cntrl.h>

#include <runa/foundation/app_base.h>

using namespace runa;

color_cntrl::color_cntrl()
{
    add_view<color_view_impl>();
}

color_cntrl::~color_cntrl()
{
    close();
}

void color_cntrl::open(const model_type& _input, model_type::on_result _on_result)
{
    model_ = { _input, _on_result };

    auto& vi = app::show_view<color_view_impl>(view_);
    vi.set_model_proxy(model_);
}

void color_cntrl::close()
{
    close_view(view_);
}

