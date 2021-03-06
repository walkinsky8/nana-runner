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

#include <nana/gui/widgets/form.hpp>

namespace runa {

    using form_base = nana::drawerbase::form::form_base;
    using form = nana::form;
    using nested_form = nana::nested_form;

    class form_base_cfg : public widget_cfg
    {
        using super = widget_cfg;
        using ui_type = form_base;

        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);
        NAR_FIELD(optional<bool>, taskbar);
        NAR_FIELD(optional<bool>, floating);
        NAR_FIELD(optional<bool>, no_activate);
        NAR_FIELD(optional<bool>, minimize);
        NAR_FIELD(optional<bool>, maximize);
        NAR_FIELD(optional<bool>, sizable);
        NAR_FIELD(optional<bool>, decoration);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
            NAR_CODEC(_s, taskbar);
            NAR_CODEC(_s, floating);
            NAR_CODEC(_s, no_activate);
            NAR_CODEC(_s, minimize);
            NAR_CODEC(_s, maximize);
            NAR_CODEC(_s, sizable);
            NAR_CODEC(_s, decoration);
        }

        void init_widget(widget& _w, view_obj* _root_view) const override;

        bool has_child_div() const override { return true; }

        point get_pos(size) const override;

        virtual nana::appearance get_appearance() const;

    };

    class form_cfg : public form_base_cfg
    {
        NAR_DEFINE_WIDGET(form, form_base_cfg);

    public:
        wnd_ptr create_wnd(window p, bool v) const override;

    };

    class nested_form_cfg : public form_base_cfg
    {
        NAR_DEFINE_WIDGET(nested_form, form_base_cfg);

    public:
        wnd_ptr create_wnd(window p, bool v) const override;

    };

}
