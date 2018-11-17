// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/login_cntrl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;
using namespace nana::runner;

login_cntrl::login_cntrl()
{
    add_view<login_view_impl>();

    model_.username_() = "guest";
    model_.password_() = "123456";
}

login_cntrl::~login_cntrl()
{
    close();
}

void login_cntrl::open(callback _on_login_success)
{
    on_login_success_ = _on_login_success;

    auto& vi = app::show_view<login_view_impl>(view_);
    vi.set_model_proxy({ model_, [&](const login_model& _m) { on_login(_m); } });
}

void login_cntrl::close()
{
    close_view(view_);
}

void login_cntrl::on_login(const login_model& _model)
{
    model_ = _model;
    if (!check_model())
    {
        nana::msgbox mb("ERROR");
        mb << "Mismatched username or password!";
        mb.show();
        //close();
    }
    else
    {
        close();
        if (on_login_success_)
            on_login_success_();
    }
}

bool login_cntrl::check_model() const
{
    return model_.username_() == "guest" && model_.password_() == "123456";
}

