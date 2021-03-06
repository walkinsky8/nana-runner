/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/04
#pragma once

#include <runa/base/_config.h>

#include <runa/base/mt_mutex.h>
#include <runa/base/mt_cond.h>
#include <runa/base/mt_lock.h>
#include <queue>

namespace runa { namespace mt {

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

}}
