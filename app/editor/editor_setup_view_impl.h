/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/11
#pragma once

#include "editor_setup_view.h"

#include "editor_setup_model.h"

#include <runa/foundation/font/font_cntrl.h>
#include <runa/foundation/color/color_cntrl.h>

namespace runa { namespace editor {

    class editor_setup_view_impl: public editor_setup_view
    {
        NAR_DEFINE_VIEW_IMPL(editor_setup);

        NAR_FIELD(editor_setup_model, model);

        widget* target_{};

        callback fn_update_{};

        font_cntrl font_cntrl_;
        color_cntrl color_cntrl_;

    public:
        editor_setup_view_impl(runa::widget_cfg& _cfg, nana::window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_target(widget* _target);

    private:
        void init();

        void on_fini() override;

        void on_font_setup(textbox& _w, font_model& _f);

        void on_color_setup(combox& _w, color_model& _c);

        void init_model();

        void update_model();

        void load_model();

        void save_model();

        void load_widget(const widget& _w);

        void save_widget(widget& _w) const;

        widget& target()
        {
            return target_ ? *target_ : caption_;
        }

    };

}}

