/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/16
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/menubar.hpp>

namespace runa {

    using menubar = nana::menubar;

    class menubar_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(menubar, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
