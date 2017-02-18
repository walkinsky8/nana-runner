// Created by walkinsky(lyh6188@hotmail.com), 2017/01/17
#pragma once

#include <nana/runner/base.h>

namespace nana::runner
{
    template<class K, class V>
    class list_map
    {
        std::vector<K> list_;
        std::map<K, V> map_;

    public:
        const std::vector<K>& list() const
        {
            return list_;
        }

        const std::map<K, V>& map() const
        {
            return map_;
        }

        void clear()
        {
            list_.clear();
            map_.clear();
        }

        void add(K k, V v)
        {
            list_.push_back(k);
            map_[k] = std::move(v);
        }

        bool get(K k, V& v) const
        {
            auto i = map_.find(k);
            if (i == map_.end())
                return false;
            _v = i->second;
            return true;
        }

    };

}
