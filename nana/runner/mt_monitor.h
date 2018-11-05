// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <mutex>
#include <condition_variable>

namespace nana::runner::mt {

    template<class _Mutex>
    class monitor
    {
    public:
        typedef _Mutex _Mtx;
        typedef std::lock_guard<_Mtx> _Lock;
        typedef std::condition_variable_any _Cond;
    private:
        _Mutex mtx_;
        _Cond cond_;

    public:
        void lock()
        {
            mtx_.lock();
        }

        void unlock()
        {
            mtx_.unlock();
        }

        void notify_one() noexcept
        {
            cond_.notify_one();
        }

        void notify_all() noexcept
        {
            cond_.notify_all();
        }

        void wait()
        {
            cond_.wait(mtx_);
        }
        
    };

}
