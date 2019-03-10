/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/12
#pragma once

#include <runa/editor/editor_view.h>

namespace runa { namespace editor {

    class editor_view_impl: public editor_view
    {
        NAR_DEFINE_VIEW_IMPL(editor);

    private:
        view_ptr curr_run_;
        cfg_ptr curr_cfg_;

    public:
        editor_view_impl(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

    protected:
        void on_fini() override;

    private:
        void init();

        void on_choose_dir();

        void on_open_file();

        void on_load();

        void on_save();

        void on_run();

        void close_current();

        void init_files();

    };

}}

