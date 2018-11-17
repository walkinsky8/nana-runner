// Created by walkinsky(lyh6188@hotmail.com), 2018/11/17
#include "stdafx.h"

#include <nana/runner/sample/demo_cntrl.h>

#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/color_view.h>
#include <nana/runner/sample/font_view.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

demo_cntrl::demo_cntrl()
{
    add_view<demo_view>();
    add_view<hello_view>();
    add_view<color_view>();
    add_view<font_view>();

    init();
}

void demo_cntrl::init()
{
}

void demo_cntrl::open()
{
    app::show_view<demo_view>(demo_);
    app::show_view<hello_view>(hello_);
    app::show_view<color_view>(color_);
    app::show_view<font_view>(font_);
}

void demo_cntrl::close()
{
    close_view(demo_);
    close_view(hello_);
    close_view(color_);
    close_view(font_);
}

