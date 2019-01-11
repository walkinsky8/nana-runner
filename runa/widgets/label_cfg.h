/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/11/15
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/label.hpp>

namespace runa {

    using label = nana::label;

    class label_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(label, widget_cfg);

        NAR_FIELD(optional<bool>, transparent);
        NAR_FIELD(optional<bool>, format);
        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, transparent);
            NAR_CODEC(_s, format);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    template<class T>
    inline void operator<<(label& _w, const T& _v)
    {
        string s;
        s << _v;
        _w.caption(s);
    }

    //template<class T>
    //inline void operator >> (const label& _w, T& _v)
    //{
    //    _w.caption() >> _v;
    //}

}
