// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/logger_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void logger_view_impl::init()
{
    log_handler_ = log_handler::instance().add([&](const string& s) {
        content_.append(s, false);
    });

    wordwrap_.events().checked([&] {
        content_.line_wrapped(wordwrap_.checked());
    });

    close_.events().click([&] {
        close();
    });
    
    exit_.events().click(
        app::quit
    );
    
    content_.events().destroy([&] {
        on_fini();
    });

    form_.events().destroy([&] {
        on_fini();
    });
}

void logger_view_impl::on_fini()
{
    log_handler_->set_empty(true);
    log_handler::instance().remove(log_handler_);
}

