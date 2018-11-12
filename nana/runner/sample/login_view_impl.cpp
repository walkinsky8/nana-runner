// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/login_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void login_view_impl::init()
{
    login_.events().click([this] { on_login(); });
    close_.events().click([this] { on_close(); });
}

void login_view_impl::on_login()
{
    NAR_LOG("login: username=" << username_.caption() << ", password=" << password_.caption());
}

void login_view_impl::on_close()
{
    NAR_LOG("close login window");
    close();
    NAR_LOG("login cancelled, so quit program");
    app::quit();
}

