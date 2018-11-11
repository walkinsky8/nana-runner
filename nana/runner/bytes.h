// Created by walkinsky(lyh6188@hotmail.com), 2017/11/07
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/istr.h>

namespace nana::runner {

    class bytes
    {
        typedef std::string store_type;

        store_type buf_;

    public:
        bytes() {}
        bytes(istr _buf)
        {
            buf_.assign(_buf.data(), _buf.size());
        }

        operator istr() const
        {
            return istr{ buf_ };
        }

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

        static byte from_base64_char(char _c);
        
        static char to_base64_char(byte _b);

        static bool is_base64_char(char _c);

        static char peek_base64_char(istr& _s);

    };
    inline std::ostream& operator<<(std::ostream& _os, const bytes& _v)
    {
        return _os << _v.to_base64();
    }
    inline std::string& operator<<(std::string& _os, const bytes& _v)
    {
        return _os << _v.to_base64();
    }
    inline void operator>>(const std::string& _is, bytes& _v)
    {
        _v.from_base64(_is);
    }

}
