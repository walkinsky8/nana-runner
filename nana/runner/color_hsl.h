// Created by walkinsky(lyh6188@hotmail.com), 2018/12/01
#pragma once

#include <nana/runner/widget_base.h>

namespace runa
{
    class color_hsl
    {
        using self = color_hsl;

        double h_{0.0}; // 0..360
        double s_{1.0}; // 0..1
        double l_{0.5}; // 0..1

    public:
        self()
        {}
        self(double _h, double _s, double _l)
            : h_{ _h }, s_{ _s }, l_{ _l }
        {}
        self(nana::color const& c);

        operator nana::color() const
        {
            return to_color();
        }

        nana::color to_color() const
        {
            return nana::color{}.from_hsl(h_, s_, l_);
        }

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

        double l() const
        {
            return l_;
        }

        double& l()
        {
            return l_;
        }

        self& l(double _l)
        {
            l_ = _l;
            return *this;
        }

        bool operator!=(const self& _v) const
        {
            return h_ != _v.h_ || s_ != _v.s_ || l_ != _v.l_;
        }
        bool operator==(const self& _v) const
        {
            return !operator!=(_v);
        }

    };

    std::ostream& operator<<(std::ostream& _os, const color_hsl& _v);
    void operator>>(string& _is, color_hsl& _v);

}//end namespace runa

