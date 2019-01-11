/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/16
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/float_listbox.hpp>

namespace runa {

    using float_listbox = nana::float_listbox;

    class float_listbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(float_listbox, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, nana::API::make_center(300,200), true); }

        void init_widget(widget& _w, view_obj* _root_view) const override { }

    };

}
