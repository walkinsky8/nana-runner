// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

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

void nana::runner::write_console(const string& _msg)
{
    OutputDebugStringW(nana::to_wstring(_msg).c_str());
}

nana::runner::out::~out()
{
}

nana::runner::log_head::log_head(log_level _ll, pcstr _file, int _line, pcstr _func)
    : ll_{ _ll }, file_{ _file }, line_{ _line }, func_{ _func }
{
}

nana::runner::log_record::log_record(log_head && _head, string && _buf)
    : head_{ _head }, buf_{ _buf }
{
}

void nana::runner::log_record::write() const
{
    std::ostringstream oss;

    pcstr beg = head_.func_;
    pcstr end = beg + std::strlen(beg);
    pcstr p = end;
    int num = 2;
    while (num-- > 0)
    {
        if (p > beg)
            --p;
        while (p > beg && (*p != ':' || *(p - 1) != ':'))
        {
            --p;
        }
    }
    if (*p == ':')
        ++p;
    pcstr classfunc = p;

    oss << head_.dt_
        << "[" << enum_log_level{ head_.ll_ }.str() << "]"
        << "" << classfunc
        << "(" << fs::path{ head_.file_ }.filename() << ":" << head_.line_ << ")"
        << " " << buf_;

    __log_handler(oss.str());
}

nana::runner::log::log(log_level _ll, pcstr _file, int _line, pcstr _func)
    : head_{_ll, _file, _line, _func}
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
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, ERROR);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, WARN);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, INFO);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, DEBUG);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, VERBOSE);
    NAR_ENUM_ADD_(nana::runner::log_level, LL_, UNKNOWN, UNKNOWN);
}

void nana::runner::log_thread::put(log_record&& _record)
{
    records_.push(_record);
}

void nana::runner::log_thread::open()
{
    thr_ = std::make_shared<std::thread>(std::bind(&log_thread::run, this));
}

void nana::runner::log_thread::close()
{
    running_ = false;
    thr_->join();
    thr_ = nullptr;
}

void nana::runner::log_thread::run()
{
    while (running_)
    {
        std::queue<log_record> tmp;
        //TODO should use thread safe queue
        tmp.swap(records_);
        while (!tmp.empty() && running_)
        {
            log_record r = tmp.front();
            tmp.pop();
            r.write();
        }
        if (running_)
            nana::system::sleep(100);
    }
}

