/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/15
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/combox.hpp>

#include <runa/foundation/color/color_model.h>

namespace runa {

    using combox = nana::combox;

    class combox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(combox, widget_cfg);

        NAR_FIELD(optional<bool>, editable);
        NAR_FIELD(optional<int>, selected);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, editable);
            NAR_CODEC(_s, selected);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    template<class E, E _V>
    void operator<<(combox& _w, const enum_<E,_V>& _v)
    {
        size_t selected = (size_t)-1;
        size_t pos = 0;
        _w.clear();
        for (auto& i : _v.v2s())
        {
            _w.push_back(i.second);
            if (_v.value() == i.first)
            {
                selected = pos;
            }
            ++pos;
        }
        if (selected!= (size_t)-1)
            _w.option(selected);
    }

    template<class E, E _V>
    void operator>>(const combox& _w, enum_<E,_V>& _v)
    {
        size_t selected = _w.option();
        size_t pos = 0;
        for (auto& i : _v.v2s())
        {
            if (selected == pos)
            {
                _v = i.first;
            }
            ++pos;
        }
    }

    inline void operator<<(combox& _w, const std::string& _v) { _w.caption(_v); }
    inline void operator<<(combox& _w, const std::wstring& _v) { _w.caption(_v); }
    inline void operator>>(const combox& _w, std::string& _v) { _v = _w.caption(); }
    inline void operator>>(const combox& _w, std::wstring& _v) { _v = _w.caption_wstring(); }

    void operator<<(combox& _w, const strings& _v);
    void operator>>(const combox& _w, strings& _v);

    void operator<<(combox& _w, const color_model& _v);
    void operator>>(const combox& _w, color_model& _v);

}

