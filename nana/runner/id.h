// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

namespace nana::runner {

    class id
    {
        std::string path_;

    public:
        id() = default;
        id(const std::string& _path)
            : path_{ _path }
        {
        }

        std::string const& str() const
        {
            return path_;
        }

        operator std::string() const
        {
            return str();
        }

        id& operator/(const id& _child)
        {
            if (!path_.empty())
                path_ << "_";
            path_ << _child;
            return *this;
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const id& _v)
    {
        return _os << _v.str();
    }
    inline std::string& operator<<(std::string& _os, const id& _v)
    {
        return _os << _v.str();
    }
    inline void operator>>(const std::string& _is, id& _v)
    {
        _v = _is;
    }

}
