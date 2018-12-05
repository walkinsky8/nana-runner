// Created by walkinsky(lyh6188@hotmail.com), 2018/10/17
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/spinbox.hpp>

namespace runa {

    using spinbox = nana::spinbox;

    class spinbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(spinbox, widget_cfg);

        NAR_FIELD(optional<bool>, editable);
        NAR_FIELD(optional<int>, begin);
        NAR_FIELD(optional<int>, last);
        NAR_FIELD(optional<int>, step);
        NAR_FIELD(string, value);
        NAR_FIELD(string, prefix);
        NAR_FIELD(string, suffix);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, editable);
            NAR_CODEC(_s, begin);
            NAR_CODEC(_s, last);
            NAR_CODEC(_s, step);
            NAR_CODEC(_s, value);
            NAR_CODEC(_s, prefix);
            NAR_CODEC(_s, suffix);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    template<class T>
    inline void operator<<(spinbox& _w, const T& _v)
    {
        string s;
        s << _v;
        //_w.caption(s);
        _w.value(s);
    }

    template<class T>
    inline void operator >> (const spinbox& _w, T& _v)
    {
        //_w.caption() >> _v;
        _w.value() >> _v;
    }

}
