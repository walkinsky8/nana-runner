// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/log.h>

#include <nana/runner/enum.h>

nana::runner::log_handler __log_handler = nana::runner::write_console;

class __loglevel__init {
public: __loglevel__init() {
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, ERROR);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, WARN);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, INFO);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, DEBUG);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, VERBOSE);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, UNKNOWN);
}
} __;

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

nana::runner::log::log(log_level _ll, pcstr _file, int _line, pcstr _func)
{
    oss_ << datetime()
        << "[" << enum_log_level{ _ll }.str() << "]"
        << "" << strings_merge(strings_sub(strings_from(_func, "::"), -2), "::")
        << "(" << fs::path{ _file }.filename() << ":" << _line << ")"
        << " ";
}

nana::runner::log::~log()
{
    oss_ << std::endl;
}

