// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/login_view.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void login_view::set_on_login(std::function<void()> _f)
{
    login_.events().click([this, _f] { close(); _f(); });
}

void login_view::init()
{
    login_.events().click([this] { on_login(); });
    close_.events().click([this] { on_close(); });
}

void login_view::on_login()
{
    NAR_LOG("login: username=" << username_.caption() << ", password=" << password_.caption());
}

void login_view::on_close()
{
    NAR_LOG("close login window");
    close();
    NAR_LOG("login cancelled, so quit program");
    app::quit();
}

