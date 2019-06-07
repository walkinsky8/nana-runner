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

#include <nana/gui/widgets/picture.hpp>

namespace runa {

    using picture = nana::picture;

    class picture_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(picture, widget_cfg);

        NAR_FIELD(string, image);
        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);
        NAR_FIELD(string, gradual_from);
        NAR_FIELD(string, gradual_to);
        NAR_FIELD(optional<bool>, gradual_horizontal);
        NAR_FIELD(optional<bool>, stretchable);
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, image);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
            NAR_CODEC(_s, gradual_from);
            NAR_CODEC(_s, gradual_to);
            NAR_CODEC(_s, gradual_horizontal);
            NAR_CODEC(_s, stretchable);
            NAR_CODEC(_s, transparent);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
