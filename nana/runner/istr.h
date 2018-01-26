// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

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

        istr substr(size_t _start, size_t _len) const
        {
            if (_start > size_)
                _start = size_;
            if (_len > size_ - _start)
                _len = size_ - _start;
            return istr{ data_ + _start, _len };
        }

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

        istr read(std::function<bool(char)> _fn)
        {
            istr& p = me();
            istr beg = p;
            while (p && _fn(*p))
                ++p;
            return istr{ beg, p };
        }

        istr read_until(std::function<bool(char)> _fn)
        {
            istr& _p = me();
            istr beg = _p;
            while (_p && !_fn(*_p))
                ++_p;
            return istr{ beg, _p };
        }

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
