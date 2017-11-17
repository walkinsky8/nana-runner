// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/istr.h>

namespace nana::runner {

    class id
    {
        static constexpr char separator = '_';

        std::string path_;

    public:
        id() = default;
        id(pcstr _path)
        {
            from(_path);
        }
        id(const string& _path)
        {
            from(_path);
        }
        id(istr _path)
        {
            from(_path);
        }

        void from(istr _path)
        {
            _path >> path_;
            format();
        }

        std::string const& str() const
        {
            return path_;
        }

        operator std::string() const
        {
            return str();
        }

        bool empty() const
        {
            return path_.empty();
        }

        id& format();

        id& operator/(const id& _child);

        bool operator==(const id& _other) const
        {
            return path_ == _other.path_;
        }
        bool operator!=(const id& _other) const
        {
            return path_ != _other.path_;
        }
        bool operator<(const id& _other) const
        {
            return path_ < _other.path_;
        }
        bool operator>(const id& _other) const
        {
            return path_ > _other.path_;
        }
        bool operator<=(const id& _other) const
        {
            return path_ <= _other.path_;
        }
        bool operator>=(const id& _other) const
        {
            return path_ >= _other.path_;
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
        _v = istr{ _is };
    }

    inline bool is_empty(const id& _v) { return _v.empty(); }

}
