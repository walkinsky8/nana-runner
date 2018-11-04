// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#include "stdafx.h"

#include <nana/runner/mt_thread.h>

void nana::runner::simple_thread::open()
{
    thr_ = std::make_shared<std::thread>(std::bind(&simple_thread::run, this));
}

void nana::runner::simple_thread::close()
{
    stop_running();
    on_close();
    thr_->join();
    thr_ = nullptr;
}

void nana::runner::simple_thread::stop_running()
{
    running_ = false;
}

void nana::runner::simple_thread::run()
{
    on_birth();
    while (running())
    {
        on_loop();
    }
    on_death();
}

