// Created by walkinsky(lyh6188@hotmail.com), 2017/01/17
#pragma once

#include <nana/runner/base.h>

namespace nana::runner
{
    template<class K, class V>
    class list_multimap
    {
    public:
        typedef std::vector<V> _List;
        typedef std::multimap<K, V> _Map;
        typedef std::pair<typename _Map::const_iterator, typename _Map::const_iterator> _Range;

    private:
        _List list_;
        _Map map_;

    public:
        bool empty() const
        {
            return list_.empty();
        }

        size_t size() const
        {
            return list_.size();
        }

        const _List& list() const
        {
            return list_;
        }

        const _Map& map() const
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
            map_.insert({ k, v });
        }

        const V* find(const K& k) const
        {
            auto i = map_.find(k);
            if (i == map_.end())
                return nullptr;
            return &i->second;
        }

        _Range equal_range(const K& k) const
        {
            return map_.equal_range(k);
        }

    };

}
