/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/21
#pragma once

#include <runa/foundation/widget_cfg.h>

namespace runa {

    struct tabpage {};

    class tabpage_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tabpage, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return nullptr; }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

        bool has_ui_widget() const override { return false; }

    };

}
