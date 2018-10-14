// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/textbox.hpp>

namespace nana::runner {

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

        void init_widget(widget& _w) const override;

    };

    template<class T>
    textbox& operator<<(textbox& _w, const T& _v)
    {
        string s;
        s << _v;
        _w.caption(s);
        return _w;
    }

    template<class T>
    void operator >> (const textbox& _w, T& _v)
    {
        string s = _w.caption();
        s >> _v;
    }

}
