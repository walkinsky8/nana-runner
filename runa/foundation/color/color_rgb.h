// Created by walkinsky(lyh6188@hotmail.com), 2018/12/03
#pragma once

#include <runa/foundation/widget_base.h>

namespace runa
{
    struct color_rgb_double {}; // r,g,b is 0..1

    class color_rgb
    {
        using self = color_rgb;
        using value_type = uint;

        value_type r_{ 0 }; // 0..255
        value_type g_{ 0 }; // 0..255
        value_type b_{ 0 }; // 0..255

    public:
        self()
        {}
        self(value_type _r, value_type _g, value_type _b)
            : r_{ _r }, g_{ _g }, b_{ _b }
        {}
        self(double _r, double _g, double _b)
            : r_{ static_cast<value_type>(_r) }, g_{ static_cast<value_type>(_g) }, b_{ static_cast<value_type>(_b) }
        {}
        self(double _r, double _g, double _b, color_rgb_double)
            : r_{ static_cast<value_type>(_r*255) }, g_{ static_cast<value_type>(_g*255) }, b_{ static_cast<value_type>(_b*255) }
        {}
        self(nana::color const& _c)
            : r_{ static_cast<value_type>(_c.r()) }, g_{ static_cast<value_type>(_c.g()) }, b_{ static_cast<value_type>(_c.b()) }
        {}
        self(const string& _s);

        operator nana::color() const
        {
            return nana::color{ r_, g_, b_ };
        }

        nana::color to_color() const
        {
            return nana::color{ r_, g_, b_ };
        }

        nana::color to_revert_color() const
        {
            return self{ 255 - r_, 255 - g_, 255 - b_ }.to_color();
        }

        string str() const;

        value_type r() const
        {
            return r_;
        }

        value_type& r()
        {
            return r_;
        }

        self& r(value_type _r)
        {
            r_ = _r;
            return *this;
        }

        value_type g() const
        {
            return g_;
        }

        value_type& g()
        {
            return g_;
        }

        self& g(value_type _g)
        {
            g_ = _g;
            return *this;
        }

        value_type b() const
        {
            return b_;
        }

        value_type& b()
        {
            return b_;
        }

        self& b(value_type _b)
        {
            b_ = _b;
            return *this;
        }

        bool operator!=(const self& _v) const
        {
            return r_ != _v.r_ || g_ != _v.g_ || b_ != _v.b_;
        }
        bool operator==(const self& _v) const
        {
            return !operator!=(_v);
        }

    };

    inline std::ostream& operator<<(std::ostream& _os, const color_rgb& _v)
    {
        return _os << _v.str();
    }

    inline void operator>>(const string& _is, color_rgb& _v)
    {
        _v = { _is };
    }

}//end namespace runa

