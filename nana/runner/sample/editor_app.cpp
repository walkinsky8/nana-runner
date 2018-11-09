// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_app.h>

#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/color_view.h>
#include <nana/runner/sample/font_view.h>

using namespace nana::runner::sample;

editor_app::editor_app()
{
    editor_cntrl::initialize();

    add_view<demo_view>();
    add_view<hello_view>();
    add_view<color_view>();
    add_view<font_view>();
}

void editor_app::on_init()
{
    editor_.on_init();
}

void editor_app::on_fini()
{
    editor_.on_fini();
}

