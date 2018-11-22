// Created by walkinsky(lyh6188@hotmail.com), 2018/11/21
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/mt_mutex.h>
#include <nana/runner/mt_lock.h>
#include <vector>

namespace nana::runner::mt {

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

}
