/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/01/18
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/categorize.hpp>

namespace runa {

    using categorize = nana::categorize<string>;

    class categorize_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(categorize, widget_cfg);

        NAR_FIELD(string, splitstr); // no effect, maybe nana has bug for categorize::tree_wrapper::path(string)

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, splitstr);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
