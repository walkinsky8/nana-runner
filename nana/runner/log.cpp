// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/log.h>

#include <nana/runner/enum.h>

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

std::ostream& nana::runner::current_info::dump(std::ostream& _os) const
{
    pcstr classfunc = find_classfunc(func_);
    _os << classfunc
        << "(" << fs::path{ file_ }.filename() << ":" << line_ << ")";
    return _os;
}

nana::runner::out::~out()
{
}

nana::runner::log_head::log_head(log_level _ll, current_info const& _current)
    : ll_{ _ll }, current_{ _current }
{
}

std::ostream& nana::runner::log_head::dump(std::ostream& _os) const
{
    _os << dt_
        << "[" << enum_log_level{ ll_ }.str() << "]"
        << current_;
    return _os;
}

nana::runner::log_record::log_record(log_head && _head, string && _buf)
    : head_{ _head }, buf_{ _buf }
{
}

std::ostream& nana::runner::log_record::dump(std::ostream& _os) const
{
    _os << head_
        << " " << buf_;
    return _os;
}

nana::runner::log::log(log_level _ll, current_info const& _current)
    : head_{_ll, _current}
{
}

nana::runner::log::~log()
{
    buf_ << std::endl;

    log_thread::instance().put(log_record{ std::move(head_), buf_.str() });
}

nana::runner::log_thread& nana::runner::log_thread::instance()
{
    static log_thread __;
    return __;
}

nana::runner::log_thread::log_thread()
{
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, EXCEPTION);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, ERROR);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, WARN);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, INFO);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, DEBUG);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, VERBOSE);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, UNKNOWN);
}

void nana::runner::log_thread::put(log_record&& _record)
{
    if (running())
    {
        records_.put(std::move(_record));
    }
    else
    {
        __log_handler(_record.str());
    }
}

void nana::runner::log_thread::on_birth()
{
}

void nana::runner::log_thread::on_death()
{
    _Q::_Queue q;
    records_.swap(q);

    std::ostringstream oss;
    while (!q.empty())
    {
        oss << q.front();
        q.pop();
    }
    __log_handler(oss.str());
}

void nana::runner::log_thread::on_loop()
{
    _Q::_Queue q;
    if (records_.get(q))
    {
        std::ostringstream oss;
        while (running() && !q.empty())
        {
            oss << q.front();
            q.pop();
        }
        __log_handler(oss.str());
    }
    if (running())
    {
        wait(500);
    }
}

void nana::runner::log_thread::on_stop()
{
    records_.cancel();
    wakeup();
}

#endif

