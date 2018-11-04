// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <mutex>
#include <condition_variable>

namespace nana::runner::mt {

    template<class _Mutex>
    class monitor
    {
        _Mutex mtx_;
        std::condition_variable_any cond_;

    public:
        void lock()
        {
            mtx_.lock();
        }

        void unlock()
        {
            mtx_.unlock();
        }

        void notify() noexcept
        {
            cond_.notify_all();
        }

        void wait()
        {
            cond_.wait(mtx_);
        }
        
    };

}
