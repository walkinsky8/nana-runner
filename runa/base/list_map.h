/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/01/17
#pragma once

#include <runa/base/_config.h>

namespace runa
{
    template<class K, class V>
    class list_map
    {
    public:
        typedef std::vector<V> _List;
        typedef std::map<K, V> _Map;
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
            map_[k] = v;
        }

        bool get(const K& k, V& v) const
        {
            auto i = map_.find(k);
            if (i == map_.end())
                return false;
            v = i->second;
            return true;
        }

        const V* find(const K& k) const
        {
            auto i = map_.find(k);
            if (i == map_.end())
                return nullptr;
            return &i->second;
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
