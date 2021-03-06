/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/14
#pragma once

#include <runa/foundation/widget_cfg.h>

namespace runa {

    struct option {};

    class option_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(option, widget_cfg);

        NAR_FIELD(string, image);
        NAR_FIELD(optional<unsigned>, width);
        NAR_FIELD(optional<bool>, check);
        NAR_FIELD(string, _click);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, image);
            NAR_CODEC(_s, width);
            NAR_CODEC(_s, check);
            NAR_CODEC(_s, _click);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

        bool has_ui_widget() const override { return false; }

        bool empty() const
        {
            return id_().empty() && caption_().empty() && !children_().size();
        }

    };

}
