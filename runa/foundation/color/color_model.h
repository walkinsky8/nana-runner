/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/11
#pragma once

#include <runa/foundation/model_base.h>

#include <runa/foundation/widget_base.h>

namespace runa {

    class color_model : public model_obj, public model_proxy_base<color_model>
    {
        NAR_DEFINE_MODEL(color, model_obj);

        NAR_FIELD(string, value);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, value);
        }

    public:
        self() = default;
        self(const color& _v);
        self(const string& _v);

        color to_color() const;
        string to_string() const;

        operator color() const
        {
            return to_color();
        }
        operator string() const
        {
            return to_string();
        }

        bool empty() const
        {
            return value_().empty();
        }

    };

    inline void operator<<(color_model& _o, const color& _v)
    {
        _o = _v;
    }
    inline void operator>>(const color_model& _i, color& _v)
    {
        _v = _i;
    }

    inline std::ostream& operator<<(std::ostream& _os, const color_model& _v)
    {
        return _os << _v.value_();
    }
    inline string& operator<<(string& _os, const color_model& _v)
    {
        return _os << _v.value_();
    }
    inline void operator>>(const string& _is, color_model& _v)
    {
        _v = _is;
    }

}

