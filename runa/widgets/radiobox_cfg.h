/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/01/08
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <runa/foundation/radiobox.h>

namespace runa {

    class radiobox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(radiobox, widget_cfg);

        NAR_FIELD(optional<bool>, check);
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, check);
            NAR_CODEC(_s, transparent);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    void radio_group_init(nana::radio_group& _group, std::vector<nana::checkbox*> _radios);

}
