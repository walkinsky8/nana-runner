// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/mt_thread.h>

void runa::simple_thread::start()
{
    if (!thr_)
        thr_ = std::make_shared<std::thread>(std::bind(&simple_thread::run, this));
}

void runa::simple_thread::stop()
{
    running(false);

    on_stop();

    wakeup();

    thread_ptr thr = thr_;
    if (thr)
    {
        thr_->join();
        thr_ = nullptr;
    }
}

void runa::simple_thread::run()
{
    running_ = true;

    on_birth();
    while (running())
    {
        if (!paused())
            on_loop();
        else
            wait(100);
    }
    on_death();
}

void runa::simple_thread::running(bool _running)
{
    running_ = _running;
    wakeup();
}

bool runa::simple_thread::running() const
{
    return running_;
}

void runa::simple_thread::pause()
{
    paused_ = true;
    wakeup();
}

void runa::simple_thread::resume()
{
    paused_ = false;
    wakeup();
}

bool runa::simple_thread::paused() const
{
    return paused_;
}

void runa::simple_thread::wakeup()
{
    mon_.notify_all_with_lock();
}

void runa::simple_thread::wait()
{
    mon_.wait_with_lock();
}

void runa::simple_thread::wait(unsigned _milliseconds)
{
    mon_.wait_with_lock(_milliseconds);
}

void runa::simple_thread::sleep(unsigned _milliseconds)
{
    nana::system::sleep(_milliseconds);
}

#endif

