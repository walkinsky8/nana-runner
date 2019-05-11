/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#include "stdafx.h"

#include "logger_view_impl.h"

#include <runa/foundation/view_impl_base.h>

using namespace runa::editor;

void logger_view_impl::init()
{
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

void logger_view_impl::init_log_handler()
{
    log_handler_ = log_handler::instance().add([&](const string& s) {
        content_.append(s, false);
    });
}

void logger_view_impl::on_fini()
{
    log_handler::instance().remove(log_handler_);
}

