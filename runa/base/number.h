/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/12
#pragma once

#include <runa/base/_config.h>

namespace runa {

    template<class T>
    class number
    {
        T value_{};

    public:
        number() = default;
        number(const number& _other) = default;
        number(number&& _other) = default;
        number(const T& _value)
            : value_{ _value }
        {}

        number& operator=(const number& _other) = default;
        number& operator=(number&& _other) = default;

        T& value()
        {
            return value_;
        }

        const T& value() const
        {
            return value_;
        }

    };
    template<class T>
    inline std::ostream& operator<<(std::ostream& _os, const number<T>& _v)
    {
        return _os << _v.value();
    }
    inline std::ostream& operator<<(std::ostream& _os, const number<int8>& _v)
    {
        return _os << static_cast<int16>(_v.value());
    }
    inline std::ostream& operator<<(std::ostream& _os, const number<uint8>& _v)
    {
        return _os << static_cast<uint16>(_v.value());
    }
    template<class T>
    inline std::istream& operator>>(std::istream& _is, number<T>& _v)
    {
        return _is >> _v.value();
    }
    inline std::istream& operator>>(std::istream& _is, number<int8>& _v)
    {
        int16 i = 0;
        _is >> i;
        _v = static_cast<int8>(i);
        return _is;
    }
    inline std::istream& operator>>(std::istream& _is, number<uint8>& _v)
    {
        uint16 i = 0;
        _is >> i;
        _v = static_cast<uint8>(i);
        return _is;
    }

}

