// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/log.h>

#include <nana/runner/enum.h>

using namespace nana::runner;

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
    if (_record.head().ll_ <= log_level::LL_ERROR)
    {
        nana::msgbox mb{ enum_log_level{_record.head().ll_}.str() };
        mb << _record.buf();
        mb.show();
    }

    if (running())
    {
        records_.put(std::move(_record));
    }
    else
    {
        log_handler::instance()(_record.str());
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
    log_handler::instance()(oss.str());
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
        log_handler::instance()(oss.str());
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

log_handler& log_handler::instance()
{
    static log_handler __;
    return __;
}

log_handler::log_handler()
{
    add(write_console);
}

log_handler::func_ptr log_handler::add(func _f)
{
    auto p = std::make_shared<optional<func>>(_f);
    funcs_.push_back(p);
    return p;
}

void log_handler::remove(func_ptr _p)
{
    funcs_.erase(_p);
}

void log_handler::operator()(const string& _msg)
{
    for (auto& i : funcs_.container())
    {
        auto& p = *i;
        if (!p.empty())
            p.value()(_msg);
    }
}

#endif

