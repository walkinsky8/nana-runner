// Created by walkinsky(lyh6188@hotmail.com), 2018/11/15
#include "stdafx.h"

#include <nana/runner/sample/demo_app.h>

#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/color_view.h>
#include <nana/runner/sample/font_view.h>

using namespace nana::runner::sample;

demo_app::demo_app()
{
    add_view<hello_view>();
    add_view<demo_view>();
    add_view<color_view>();
    add_view<font_view>();
}

void demo_app::on_init()
{
    show_view_(L"demo");
    show_view_(L"hello");
    show_view_(L"font");
    show_view_(L"color");
}

void demo_app::on_fini()
{
}

