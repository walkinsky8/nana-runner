// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/mt_mutex.h>
#include <nana/runner/mt_cond.h>
#include <nana/runner/mt_lock.h>
#include <queue>

namespace nana::runner::mt {

    template<class T>
    class queue
    {
    public:
        typedef mt::mutex _Mtx;
        typedef mt::condition_variable _Cond;
        typedef mt::unique_lock<_Mtx> _Lock;
        typedef std::queue<T> _Queue;

    private:
        _Mtx mtx_;
        _Cond cond_;
        _Queue q_;

    public:
        void put(T&& _v)
        {
            _Lock __(mtx_);
            q_.push(_v);
            cond_.notify_one();
        }

        bool get(T& _v)
        {
            _Lock __(mtx_);
            if (q_.empty())
                cond_.wait(__);
            if (q_.empty())
                return false;
            _v = q_.front();
            q_.pop();
            return true;
        }

        bool get(_Queue& _v)
        {
            _Lock __(mtx_);
            if (q_.empty())
                cond_.wait(__);
            if (q_.empty())
                return false;
            _v.swap(q_);
            return true;
        }

        void cancel()
        {
            _Lock __(mtx_);
            cond_.notify_all();
        }

        void swap(_Queue& _v)
        {
            _Lock __(mtx_);
            _v.swap(q_);
        }

    };

}
