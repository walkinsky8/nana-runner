// Created by walkinsky(lyh6188@hotmail.com), 2018/10/14
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/group.hpp>

namespace nana::runner {

    using group = nana::group;

    class group_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(group, widget_cfg);

        NAR_FIELD(optional<align>, caption_align);
        NAR_FIELD(optional<bool>, radio_mode);
        NAR_FIELD(optional<bool>, enable_format_caption);

        mutable std::vector<checkbox*> m_radios;

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, caption_align);
            NAR_CODEC(_s, radio_mode);
            NAR_CODEC(_s, enable_format_caption);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, nana::rectangle{}, v); }

        void init_widget(widget& _w) const override;

        bool has_child_div() const override { return false; }

        std::vector<checkbox*>& radios() { return m_radios; }

    };

    inline void init_group(group& _w, const strings& _names, std::function<void()> _fn)
    {
        for (auto& i : _names)
        {
            auto& o = _w.add_option(i);
            if (_fn)
                o.events().click(_fn);
        }
    }

    template<class E, E _V>
    void init_group(group& _w, const enum_<E, _V>& _v, std::function<void()> _fn)
    {
        strings names;
        names << _v;
        init_group(_w, names, _fn);
    }

    template<class E, E _V>
    group& operator<<(group& _w, const enum_<E, _V>& _v)
    {
        strings names;
        names << _v;
        init_group(_w, names, nullptr);
        return _w;
    }

    template<class E, E _V>
    void operator >> (const group& _w, enum_<E, _V>& _v)
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

}