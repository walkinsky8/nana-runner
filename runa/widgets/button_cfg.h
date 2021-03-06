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

#include <nana/gui/widgets/button.hpp>

namespace runa {

    using button = nana::button;

    class button_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(button, widget_cfg);

        NAR_FIELD(string, icon);
        NAR_FIELD(optional<bool>, enable_pushed);
        NAR_FIELD(optional<bool>, pushed);
        NAR_FIELD(optional<bool>, omitted);
        NAR_FIELD(optional<bool>, enable_focus_color);
        NAR_FIELD(optional<bool>, transparent);
        NAR_FIELD(optional<bool>, edge_effects);
        NAR_FIELD(string, _click);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, icon);
            NAR_CODEC(_s, enable_pushed);
            NAR_CODEC(_s, pushed);
            NAR_CODEC(_s, omitted);
            NAR_CODEC(_s, enable_focus_color);
            NAR_CODEC(_s, transparent);
            NAR_CODEC(_s, edge_effects);
            NAR_CODEC(_s, _click);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
