// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/logger_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void logger_view_impl::init()
{
    old_handler_ = set_log_handler([this](const string& s) {
        write_console(s);
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
    
    form_.events().destroy([&] {
        set_log_handler(old_handler_);
    });
}

