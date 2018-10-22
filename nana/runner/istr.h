// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base_config.h>

namespace nana::runner {

    class istr
    {
        size_t size_{};
        pcstr data_{};

    public:
        istr() = default;
        istr(const string& _s)
            : size_{ _s.size() }, data_ {_s.data()}
        {}
        istr(pcstr _s)
            : size_{ (!_s ? 0 : std::char_traits<char>::length(_s)) }, data_{ _s }
        {}
        istr(pcstr _s, size_t _n)
            : size_(_n), data_{ _s }
        {}
        istr(pcstr _b, pcstr _e)
            : size_(_e - _b), data_{_b}
        {}
        istr(istr _b, istr _e)
            : size_{static_cast<size_t>(_e.begin() - _b.begin())}, data_{ _b.begin() }
        {}

        void operator >> (string& s) const
        {
            s.assign(data(), size());
        }

        operator string() const
        {
            string s;
            *this >> s;
            return s;
        }

        string operator+(istr _other) const
        {
            string s;
            *this >> s;
            return s.append(_other.data(), _other.size());
        }

        operator void*() const
        {
            return (void*)!empty();
        }

        bool operator!() const
        {
            return empty();
        }

        bool empty() const
        {
            return !data_ || !size_;
        }

        pcstr data() const
        {
            return data_;
        }

        size_t size() const
        {
            return size_;
        }

        pcstr begin() const
        {
            return data_;
        }

        pcstr end() const
        {
            return begin() + size();
        }

        char operator*() const
        {
            return empty() ? 0 : *data();
        }

        char operator[](size_t _i) const
        {
            return empty() ? 0 : data()[_i];
        }

        istr& operator++()
        {
            return advance(1);
        }

        istr& operator--()
        {
            return advance(-1);
        }

        istr operator++(int)
        {
            istr bak = me();
            ++me();
            return bak;
        }

        istr operator--(int)
        {
            istr bak = me();
            --me();
            return bak;
        }

        istr& operator+=(int _offset)
        {
            return advance(_offset);
        }

        istr& operator-=(int _offset)
        {
            return advance(-_offset);
        }

        istr& advance(int _offset = 1);

        istr operator+(int _offset) const
        {
            istr tmp = me();
            tmp += _offset;
            return tmp;
        }

        istr operator-(int _offset) const
        {
            istr tmp = me();
            tmp -= _offset;
            return tmp;
        }

        int operator-(istr _other) const
        {
            return int(data_ - _other.data_);
        }

        istr substr(size_t _start, size_t _len) const;

        istr leftstr(size_t _len) const
        {
            return substr(0, _len);
        }

        istr rightstr(size_t _len) const
        {
            if (_len > size())
                _len = size();
            return substr(size() - _len, _len);
        }

        const istr& me() const
        {
            return *this;
        }

        istr& me()
        {
            return *this;
        }

        istr& clear()
        {
            data_ = nullptr;
            size_ = 0;
            return *this;
        }

        char read()
        {
            return *me()++;
        }

        istr read(size_t _n)
        {
            istr s = leftstr(_n);
            me() += (int)_n;
            return s;
        }

        istr read(std::function<bool(char)> _fn, size_t _maxLen = npos);

        istr read_until(std::function<bool(char)> _fn, size_t _maxLen = npos);

        int compare(istr _v) const;

        bool operator==(istr _v) const
        {
            return me().compare(_v) == 0;
        }
        bool operator!=(istr _v) const
        {
            return me().compare(_v) != 0;
        }
        bool operator<(istr _v) const
        {
            return me().compare(_v) < 0;
        }
        bool operator<=(istr _v) const
        {
            return me().compare(_v) <= 0;
        }
        bool operator>(istr _v) const
        {
            return me().compare(_v) > 0;
        }
        bool operator>=(istr _v) const
        {
            return me().compare(_v) >= 0;
        }

        bool to_bool() const
        {
            return !empty() && me() != istr("0") && me() != istr("false");
        }

        int8 to_int8() const
        {
            return static_cast<int8>(to_long());
        }

        uint8 to_uint8() const
        {
            return static_cast<uint8>(to_long());
        }

        short to_short() const
        {
            return static_cast<short>(to_long());
        }

        ushort to_ushort() const
        {
            return static_cast<ushort>(to_ulong());
        }

        int to_int() const
        {
            return static_cast<int>(to_long());
        }

        uint to_uint() const
        {
            return static_cast<uint>(to_ulong());
        }

        long to_long() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtol(s.data(), &e, 10);
        }

        ulong to_ulong() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtoul(s.data(), &e, 10);
        }

        longlong to_longlong() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtoll(s.data(), &e, 10);
        }

        ulonglong to_ulonglong() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtoull(s.data(), &e, 10);
        }

        float to_float() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtof(s.data(), &e);
        }

        double to_double() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtod(s.data(), &e);
        }

        long double to_longdouble() const
        {
            string s;
            me() >> s;
            char* e = 0;
            return std::strtold(s.data(), &e);
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const istr& _v)
    {
        if (!_v.empty())
            _os.write(_v.begin(), _v.size());
        return _os;
    }
    inline std::string& operator<<(std::string& _os, const istr& _v)
    {
        return _os.append(_v.data(), _v.size());
    }
    inline string operator+(istr _v1, pcstr _v2)
    {
        string s;
        _v1 >> s;
        s += _v2;
        return s;
    }
    inline string operator+(pcstr _v1, istr _v2)
    {
        string s(_v1);
        s.append(_v2.data(), _v2.size());
        return s;
    }

}
