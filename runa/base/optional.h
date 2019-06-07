/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/01/20
#pragma once

#include <runa/base/_config.h>

namespace runa {

    template<class T>
    class optional
    {
        T value_{};
        volatile bool empty_{ true };

    public:
        optional() = default;
        optional(const optional& _other) = default;
        optional(optional&& _other) = default;
        optional(const T& _value)
            : value_{ _value }, empty_{ false }
        {}

        optional& operator=(const optional& _other) = default;
        optional& operator=(optional&& _other) = default;

        void set_value(const T& _v)
        {
            value_ = _v;
            empty_ = false;
        }

        void set_empty(bool _empty)
        {
            empty_ = _empty;
        }

        const T& value() const
        {
            return value_;
        }

        bool empty() const
        {
            return empty_;
        }

    };
    template<class T>
    inline std::ostream& operator<<(std::ostream& _os, const optional<T>& _v)
    {
        if (!_v.empty())
            _os << _v.value();
        return _os;
    }
    template<class T>
    inline std::string& operator<<(std::string& _os, const optional<T>& _v)
    {
        if (!_v.empty())
            _os << _v.value();
        return _os;
    }

    template<class T>
    inline bool is_empty(const optional<T>& _v) { return _v.empty(); }

}
