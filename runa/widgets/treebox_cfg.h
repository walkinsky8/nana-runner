/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/10/20
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <runa/widgets/option_cfg.h>

#include <nana/gui/widgets/treebox.hpp>

namespace runa {

    using treebox = nana::treebox;
    using nana::drawerbase::treebox::item_proxy;

    class treebox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(treebox, widget_cfg);

        NAR_FIELD(optional<bool>, checkable);
        NAR_FIELD(string, directory);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, checkable);
            NAR_CODEC(_s, directory);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

        static void init_nodes(treebox& _w, item_proxy _p, option_cfg& _c);

    };

}
