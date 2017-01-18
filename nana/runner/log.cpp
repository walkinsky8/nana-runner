// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/log.h>

nana::runner::log_handler __log_handler = nana::runner::write_console;

nana::runner::log_handler nana::runner::get_log_handler()
{
    return __log_handler;
}
nana::runner::log_handler nana::runner::set_log_handler(log_handler lh)
{
    log_handler old = get_log_handler();
    __log_handler = lh;
    return old;
}

void nana::runner::write_console(const string& _msg)
{
    OutputDebugStringW(nana::to_wstring(_msg).c_str());
}

nana::runner::out::~out()
{
    __log_handler(oss_.str());
}

nana::runner::log::log()
{
    oss_ << "--- ";
}

nana::runner::log::~log()
{
    oss_ << std::endl;
}

