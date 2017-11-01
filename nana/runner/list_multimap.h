// Created by walkinsky(lyh6188@hotmail.com), 2017/01/17
#pragma once

#include <nana/runner/base.h>

namespace nana::runner
{
    template<class K, class V>
    class list_multimap
    {
        std::vector<V> list_;
        std::multimap<K, V> map_;

    public:
        void add(const K& k, const V& v)
        {
            list_.push_back(v);
            map_.insert({ k, v });
        }

        const std::vector<K>& list() const
        {
            return list_;
        }

        const std::multimap<K, V> map() const
        {
            return map_;
        }

    };

}
