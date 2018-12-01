// Created by walkinsky(lyh6188@hotmail.com), 2018/12/01
#pragma once

#include <nana/runner/widget_base.h>

namespace runa
{
    class color_hsv
    {
        using self = color_hsv;

        double h_{0.0}; // 0..360
        double s_{1.0}; // 0..1
        double v_{1.0}; // 0..1

    public:
        self()
        {}
        self(double _h, double _s, double _v)
            : h_{ _h }, s_{ _s }, v_{ _v }
        {}
        self(color const& c);

        operator nana::color() const
        {
            return to_color();
        }

        nana::color to_color() const;

        nana::color to_revert_color() const
        {
            nana::color c = to_color();
            return nana::color{ static_cast<uint>(255 - c.r()), static_cast<uint>(255 - c.g()), static_cast<uint>(255 - c.b()) };
        }

        double h() const
        {
            return h_;
        }

        double& h()
        {
            return h_;
        }

        self& h(double _h)
        {
            h_ = _h;
            return *this;
        }

        double s() const
        {
            return s_;
        }

        double& s()
        {
            return s_;
        }

        self& s(double _s)
        {
            s_ = _s;
            return *this;
        }

        double v() const
        {
            return v_;
        }

        double& v()
        {
            return v_;
        }

        self& v(double _v)
        {
            v_ = _v;
            return *this;
        }

        bool operator!=(const self& _v) const
        {
            return h_ != _v.h_ || s_ != _v.s_ || v_ != _v.v_;
        }
        bool operator==(const self& _v) const
        {
            return !operator!=(_v);
        }

    };

    std::ostream& operator<<(std::ostream& _os, const color_hsv& _v);
    void operator>>(string& _is, color_hsv& _v);

}//end namespace runa

