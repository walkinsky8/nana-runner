/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/01/03
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <runa/foundation/color/color_chooser.h>

namespace runa {

    class color_chooser_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(color_chooser, widget_cfg);

        NAR_FIELD(optional<enum_color_mode>, mode);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, mode);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}

