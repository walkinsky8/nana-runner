// Created by walkinsky(lyh6188@hotmail.com), 2017/01/20
#pragma once

#include <nana/runner/base_config.h>

namespace nana::runner {

    template<class T>
    class optional
    {
        T value_{};
        bool empty_{ true };

    public:
        optional() = default;
        optional(const optional& _other) = default;
        optional(optional&& _other) = default;
        optional(const T& _value)
            : value_{ _value }, empty_{ false }
        {}

        optional& operator=(const optional& _other) = default;
        optional& operator=(optional&& _other) = default;

        T& value()
        {
            return value_;
        }

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

		bool valid() const
		{
			return !empty_;
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
