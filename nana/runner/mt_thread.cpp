// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/mt_thread.h>

void nana::runner::simple_thread::start()
{
    thr_ = std::make_shared<std::thread>(std::bind(&simple_thread::run, this));
}

void nana::runner::simple_thread::stop()
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

void nana::runner::simple_thread::run()
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

void nana::runner::simple_thread::running(bool _running)
{
    running_ = _running;
    wakeup();
}

bool nana::runner::simple_thread::running() const
{
    return running_;
}

void nana::runner::simple_thread::pause()
{
    paused_ = true;
    wakeup();
}

void nana::runner::simple_thread::resume()
{
    paused_ = false;
    wakeup();
}

bool nana::runner::simple_thread::paused() const
{
    return paused_;
}

void nana::runner::simple_thread::wakeup()
{
    mon_.notify_all_with_lock();
}

void nana::runner::simple_thread::wait()
{
    mon_.wait_with_lock();
}

void nana::runner::simple_thread::wait(unsigned _milliseconds)
{
    mon_.wait_with_lock(_milliseconds);
}

void nana::runner::simple_thread::sleep(unsigned _milliseconds)
{
    nana::system::sleep(_milliseconds);
}

#endif

