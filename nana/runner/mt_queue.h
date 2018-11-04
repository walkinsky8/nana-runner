// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <nana/runner/mt_mutex.h>
#include <nana/runner/mt_monitor.h>
#include <nana/runner/mt_lock.h>
#include <nana/runner/mt_queue.h>

namespace nana::runner::mt {

    template<class T>
    class queue
    {
        typedef mt::mutex _Mtx;
        typedef mt::monitor<_Mtx> _Mon;
        typedef mt::lock_guard<_Mon> _Lock;
        typedef std::queue<T> _Queue;
        _Mon mon_;
        _Queue q_;

    public:
        void put(T&& _v)
        {
            _Lock __(mon_);
            q_.push(_v);
            mon_.notify();
        }

        bool get(T& _v)
        {
            _Lock __(mon_);
            if (q_.empty())
                mon_.wait();
            if (q_.empty())
                return false;
            _v = q_.front();
            q_.pop();
            return true;
        }

        void notify()
        {
            _Lock __(mon_);
            mon_.notify();
        }

    };

}
