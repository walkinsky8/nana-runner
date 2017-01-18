// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

namespace nana::runner {

    class istr
    {
        pcstr begin_{};
        pcstr end_{};

    public:
        istr() = default;
        istr(const string& _s)
            : begin_{ _s.data() }, end_{ _s.data() + _s.size() }
        {}
        istr(pcstr _s)
            : begin_{ _s }, end_{ _s + (!_s ? 0 : std::char_traits<char>::length(_s)) }
        {}
        istr(pcstr _s, size_t _n)
            : begin_{ _s }, end_{ _s + _n }
        {}
        istr(pcstr _b, pcstr _e)
            : begin_{_b}, end_{_e}
        {}
        istr(istr _b, istr _e)
            : begin_{ _b.begin() }, end_{ _e.begin() }
        {}

        void operator >> (string& s) const
        {
            s.assign(data(), size());
        }

        operator bool() const
        {
            return !empty();
        }

        bool operator!() const
        {
            return empty();
        }

        bool empty() const
        {
            return begin_ >= end_;
        }

        pcstr data() const
        {
            return begin_;
        }

        size_t size() const
        {
            return end_ - begin_;
        }

        pcstr begin() const
        {
            return begin_;
        }

        pcstr end() const
        {
            return end_;
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

        istr& advance(int _offset = 1)
        {
            begin_ += _offset;
            if (begin_ > end_)
                begin_ = end_;
            return *this;
        }

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
            return int(begin_ - _other.begin_);
        }

        istr substr(size_t _start, size_t _len) const
        {
            pcstr b = begin_ + _start;
            if (b > end_)
                b = end_;
            if (_len + b > end_)
                _len = end_ - b;
            return istr{ b, _len };
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

        istr read_the(std::function<bool(char)> _fn)
        {
            istr p = me();
            istr beg = p;
            while (p && _fn(*p))
                ++p;
            return istr{ beg, p };
        }

        istr read_not(std::function<bool(char)> _fn)
        {
            istr& _p = me();
            istr beg = _p;
            while (_p && !_fn(*_p))
                ++_p;
            return istr{ beg, _p };
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

}
