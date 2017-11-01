// Created by walkinsky(lyh6188@hotmail.com), 2017/01/17
#pragma once

#include <nana/runner/base.h>

namespace nana::runner
{
    template<class K, class V>
    class list_map
    {
        std::vector<V> list_;
        std::map<K, V> map_;

    public:
        bool empty() const
        {
            return list_.empty();
        }

        const std::vector<V>& list() const
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

        void add(const K& k, const V& v)
        {
            list_.push_back(v);
            map_[k] = v;
        }

        bool get(const K& k, V& v) const
        {
            auto i = map_.find(k);
            if (i == map_.end())
                return false;
            _v = i->second;
            return true;
        }

    };

}
