/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/21
#pragma once

#include <runa/base/_config.h>

#include <runa/base/mt_mutex.h>
#include <runa/base/mt_lock.h>
#include <vector>

namespace runa { namespace mt {

    template<class T>
    class vector
    {
    public:
        typedef mt::mutex _Mtx;
        typedef mt::unique_lock<_Mtx> _Lock;
        typedef std::vector<T> _Container;

    private:
        _Mtx mtx_;
        _Container container_;

    public:
        void push_back(const T& _v)
        {
            _Lock __(mtx_);
            container_.push_back(_v);
        }

        void erase(const T& _v)
        {
            _Lock __(mtx_);
            for (auto i = container_.begin(); i != container_.end(); ++i)
            {
                if (*i == _v)
                {
                    container_.erase(i);
                    break;
                }
            }
        }

        _Container container()
        {
            _Lock __(mtx_);
            return container_;
        }

    };

}}
