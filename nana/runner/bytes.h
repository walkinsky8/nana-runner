// Created by walkinsky(lyh6188@hotmail.com), 2017/11/07
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/istr.h>

namespace nana::runner {

    class bytes
    {
        typedef std::string store_type;

        store_type buf_;

    public:
        bool empty() const
        {
            return buf_.empty();
        }

        pcstr data() const
        {
            return buf_.data();
        }

        size_t size() const
        {
            return buf_.size();
        }

        void from_base64(istr _s);

        string to_base64() const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const bytes& _v)
    {
        return _os << _v.to_base64();
    }
    inline std::string& operator<<(std::string& _os, const bytes& _v)
    {
        return _os << _v.to_base64();
    }

}
