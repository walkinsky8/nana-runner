/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/04
#pragma once

#include <runa/base/_config.h>

#include <mutex>
#include <condition_variable>

namespace runa::mt {

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
        
        void wait(unsigned _milliseconds)
        {
            cond_.wait_for(mtx_, std::chrono::milliseconds(_milliseconds));
        }

        void notify_one_with_lock() noexcept
        {
            _Lock __(mtx_);
            notify_one();
        }

        void notify_all_with_lock() noexcept
        {
            _Lock __(mtx_);
            notify_all();
        }

        void wait_with_lock()
        {
            _Lock __(mtx_);
            wait();
        }

        void wait_with_lock(unsigned _milliseconds)
        {
            _Lock __(mtx_);
            wait(_milliseconds);
        }

    };

}
