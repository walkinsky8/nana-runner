/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/17
#include "stdafx.h"

#include "demo_cntrl.h"

#include "demo_view.h"
#include "hello_view.h"
#include "simple_view.h"

#include <runa/foundation/app_base.h>

using namespace runa::sample;
using namespace runa;

demo_cntrl::demo_cntrl()
{
    add_view<demo_view>();
    add_view<color_view_impl>();
    add_view<font_view_impl>();
    add_view<hello_view>();
    add_view<simple_view>();
}

void demo_cntrl::open(callback _on_complete)
{
    app::show_view<demo_view>(demo_);
    app::show_view<color_view_impl>(color_);
    app::show_view<font_view_impl>(font_);
    app::show_view<hello_view>(hello_);
    app::show_view<simple_view>(simple_);
    dummy_ = app::show_view(L"dummy");
    minimal_ = app::show_view(L"minimal");
    generic_ = app::show_view(L"generic");
}

void demo_cntrl::close()
{
    close_view(demo_);
    close_view(color_);
    close_view(font_);
    close_view(hello_);
    close_view(simple_);
    close_view(dummy_);
    close_view(minimal_);
    close_view(generic_);
}

