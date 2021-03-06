/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/11/15
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/textbox.hpp>

namespace runa {

    using textbox = nana::textbox;

    class textbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(textbox, widget_cfg);

        NAR_FIELD(optional<bool>, line_wrapped);
        NAR_FIELD(optional<bool>, multi_lines);
        NAR_FIELD(optional<bool>, editable);
        NAR_FIELD(optional<char>, mask);
        NAR_FIELD(optional<align>, align);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, line_wrapped);
            NAR_CODEC(_s, multi_lines);
            NAR_CODEC(_s, editable);
            NAR_CODEC(_s, mask);
            NAR_CODEC(_s, align);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    template<class T>
    inline void operator<<(textbox& _w, const T& _v)
    {
        string s;
        s << _v;
        _w.caption(s);
    }

    template<class T>
    inline void operator >> (const textbox& _w, T& _v)
    {
        if (!_w.caption().empty())
            _w.caption() >> _v;
    }
    inline void operator >> (const textbox& _w, string& _v)
    {
        if (!_w.caption().empty())
            _v = _w.caption();
    }

}
