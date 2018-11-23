// Created by walkinsky(lyh6188@hotmail.com), 2017/01/17
#pragma once

#include <nana/runner/_config.h>

namespace runa
{
    template<class K, class V>
    class list_multimap
    {
    public:
        typedef std::vector<V> _List;
        typedef std::multimap<K, V> _Map;
        typedef std::pair<typename _Map::const_iterator, typename _Map::const_iterator> _Range;
        typedef typename _List::const_iterator const_iterator;

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

        const_iterator begin() const
        {
            return list_.begin();
        }

        const_iterator end() const
        {
            return list_.end();
        }

    };

}
