/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/17
#pragma once

#include <runa/foundation/widget_cfg.h>

#include <nana/gui/widgets/tabbar.hpp>

#include <runa/foundation/view_base.h>

namespace runa {

    using tabbar = nana::tabbar<string>;
    using tabbar_lite = nana::tabbar_lite;

    class tabbar_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tabbar, widget_cfg);

        NAR_FIELD(id, page_id);
        NAR_FIELD(optional<bool>, close_fly);
        NAR_FIELD(optional<bool>, tb_add);
        NAR_FIELD(optional<bool>, tb_scroll);
        NAR_FIELD(optional<bool>, tb_list);
        NAR_FIELD(optional<bool>, tb_close);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            NAR_CODEC_SUPER(_s);
            NAR_CODEC(_s, page_id);
            NAR_CODEC(_s, close_fly);
            NAR_CODEC(_s, tb_add);
            NAR_CODEC(_s, tb_scroll);
            NAR_CODEC(_s, tb_list);
            NAR_CODEC(_s, tb_close);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

    class tabbar_lite_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tabbar_lite, widget_cfg);

        NAR_FIELD(id, page_id);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, page_id);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
