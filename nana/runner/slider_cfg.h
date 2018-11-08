// Created by walkinsky(lyh6188@hotmail.com), 2018/01/22
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/slider.hpp>

namespace nana::runner {

    using slider = nana::slider;

    class slider_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(slider, widget_cfg);

        NAR_FIELD(optional<bool>, vertical);
        NAR_FIELD(optional<unsigned>, maximum);
        NAR_FIELD(optional<unsigned>, value);
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, vertical);
            NAR_CODEC(_s, maximum);
            NAR_CODEC(_s, value);
            NAR_CODEC(_s, transparent);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    inline void operator<<(slider& _s, uint _v)
    {
        _s.value(_v);
    }
    inline void operator<<(slider& _s, double _v)
    {
        _s << static_cast<uint>(_v);
    }
    inline void operator>>(const slider& _s, uint& _v)
    {
        _v = _s.value();
    }
    inline void operator>>(const slider& _s, double& _v)
    {
        uint ui = 0;
        _s >> ui;
        _v = ui;
    }

}

