// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#pragma once

#include <nana/runner/model_base.h>

#include <nana/runner/widget_base.h>

namespace nana::runner {

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

    template<> struct dumpable<font_model> { static constexpr bool value = true; };

}

