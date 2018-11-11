// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_cntrl.h>

#include <nana/runner/sample/logger_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/editor_view.h>
#include <nana/runner/sample/editor_setup_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void editor_cntrl::initialize()
{
    add_view<logger_view>();
    add_view<login_view>();
    add_view<editor_view>();
    add_view<editor_setup_view_impl>();
}

void editor_cntrl::on_init()
{
    log_ = app::get_view(L"logger.nar");
    login_ = app::get_view(L"login.nar");
    editor_ = app::get_view(L"editor.nar");
    editor_setup_ = app::get_view(L"editor_setup.nar");

    log_->show();
    login_->show();
    login_->cast<login_view>().set_on_login([this] { editor_->show(); });
    editor_->cast<editor_view>().set_on_setup([this] { editor_setup_->show(); });
}

void editor_cntrl::on_fini()
{
    if (log_)
        log_->close();
    if (login_)
        login_->close();
    if (editor_)
        editor_->close();
    if (editor_setup_)
        editor_setup_->close();
}
