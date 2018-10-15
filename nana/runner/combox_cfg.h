// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/combox.hpp>

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

        void init_widget(widget& _w) const override;

        bool has_child_div() const override { return false; }

    };

    template<class E, E _V>
    combox& operator<<(combox& _w, const enum_<E,_V>& _v)
    {
        size_t selected = (size_t)-1;
        size_t pos = 0;
        for (auto& i : _v.s2v())
        {
            _w.push_back(i.first);
            if (_v.value() == i.second)
            {
                selected = pos;
            }
            ++pos;
        }
        _w.option(selected);
        return _w;
    }

    template<class E, E _V>
    void operator >> (const combox& _w, enum_<E,_V>& _v)
    {
        size_t selected = _w.option();
        size_t pos = 0;
        for (auto& i : _v.s2v())
        {
            if (selected == pos)
            {
                _v = i.second;
            }
            ++pos;
        }
    }

}
