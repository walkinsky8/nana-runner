/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/09
#pragma once

#include <runa/foundation/model_base.h>

#include <runa/foundation/widget_base.h>

namespace runa {

    class font_model : public model_obj, public model_proxy_base<font_model>
    {
        NAR_DEFINE_MODEL(font, model_obj);

        NAR_FIELD(string, name);
        NAR_FIELD_(double, size, 10);
        NAR_FIELD(bool, bold);
        NAR_FIELD(bool, italic);
        NAR_FIELD(bool, underline);
        NAR_FIELD(bool, strikeout);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            NAR_CODEC_SUPER(_s);
            NAR_CODEC(_s, name);
            NAR_CODEC(_s, size);
            NAR_CODEC(_s, bold);
            NAR_CODEC(_s, italic);
            NAR_CODEC(_s, underline);
            NAR_CODEC(_s, strikeout);
        }

    public:
        font_model();
        font_model(const font& _v);
        font_model(const string& _v);

        font to_font() const;
        string to_string() const;

        operator font() const
        {
            return to_font();
        }
        operator string() const
        {
            return to_string();
        }

    };

    inline void operator<<(font_model& _o, const font& _v)
    {
        _o = font_model{ _v };
    }
    inline void operator>>(const font_model& _i, font& _v)
    {
        _v = _i;
    }

    inline std::ostream& operator<<(std::ostream& _os, const font_model& _v)
    {
        return _os << dump(_v);
    }
    inline void operator<<(string& _os, const font_model& _v)
    {
        _os << (font)_v;
    }
    inline void operator>>(const string& _is, font_model& _v)
    {
        font f;
        _is >> f;
        _v = f;
    }

}

