// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/login_cntrl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void login_cntrl::initialize()
{
    add_view<login_view>();
}

void login_cntrl::on_init()
{
    view_ = app::show_view<login_view>();
}

void login_cntrl::on_fini()
{
    close_view(view_);
}

