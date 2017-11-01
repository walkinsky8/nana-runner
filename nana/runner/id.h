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
        id(istr _path)
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

        id& operator/(const id& _child)
        {
            if (!path_.empty())
                path_ << separator;
            path_ << _child;
            return *this;
        }

        id& format()
        {
            if (istr{ path_ }.read(is_identifier_body).size() == path_.size())
                return *this;
            for (auto i = path_.begin(); i != path_.end(); ++i)
            {
                if (!is_identifier_body(*i))
                    *i = separator;
            }
            int seps = 0;
            for (size_t i = 0; i < path_.size(); ++i)
            {
                if (path_[i] == separator)
                    ++seps;
                else
                {
                    if (seps > 1)
                    {
                        path_.erase(i - seps, seps - 1);
                        i -= seps - 1;
                    }
                    seps = 0;
                }
            }
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
        _v = istr{ _is };
    }

}
