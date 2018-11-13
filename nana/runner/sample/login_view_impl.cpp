// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/login_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;
using namespace nana::runner;

void login_view_impl::init()
{
    close_.events().click(std::bind(&self::on_close, this));
    login_.events().click(std::bind(&self::on_login, this));
}

void login_view_impl::set_model_proxy(model_proxy<login_model> const& _proxy)
{
    proxy_ = _proxy;
    
    load_model(proxy_.data_);
}

void login_view_impl::load_model(const login_model& _model)
{
    username_ << _model.username_();
    password_ << _model.password_();
}

void login_view_impl::save_model(login_model& _model) const
{
    username_ >> _model.username_();
    password_ >> _model.password_();
}

void login_view_impl::on_login()
{
    save_model(proxy_.data_);
    NAR_LOG_VAR(proxy_.data_);

    proxy_();
}

void login_view_impl::on_close()
{
    NAR_LOG("close login window");
    close();
}

