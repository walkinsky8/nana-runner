// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/combox.hpp>

#include <nana/runner/color_model.h>

namespace nana::runner {

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
        for (auto& i : _v.v2s())
        {
            _w.push_back(i.second);
            if (_v.value() == i.first)
            {
                selected = pos;
            }
            ++pos;
        }
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

