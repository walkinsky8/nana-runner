/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#pragma once

#include <runa/foundation/model_base.h>

#include <runa/foundation/widget_base.h>

namespace runa {

    class font_model : public model_obj
    {
        NAR_DEFINE_MODEL(font, model_obj);

        NAR_FIELD(string, name);
        NAR_FIELD(double, size);
        NAR_FIELD(bool, bold);
        NAR_FIELD(bool, italic);
        NAR_FIELD(bool, underline);
        NAR_FIELD(bool, strikeout);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, name);
            NAR_CODEC(_s, size);
            NAR_CODEC(_s, bold);
            NAR_CODEC(_s, italic);
            NAR_CODEC(_s, underline);
            NAR_CODEC(_s, strikeout);
        }

    public:
        font_model() = default;
        font_model(const font& _f);
        
        operator font() const;

    };

    inline void operator<<(font_model& _o, const font& _v)
    {
        _o = _v;
    }

    inline void operator>>(const font_model& _i, font& _v)
    {
        _v = _i;
    }

}

