// Created by walkinsky(lyh6188@hotmail.com), 2018/11/11
#pragma once

#include <nana/runner/sample/editor_setup_view.h>

#include <nana/runner/sample/editor_setup_model.h>

namespace nana::runner::sample {

    class editor_setup_view_impl: public editor_setup_view
    {
        NAR_DEFINE_VIEW_IMPL(editor_setup);

        NAR_FIELD(editor_setup_model, model);

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

    private:
        void init();

        void init_model();

        void load_model();

        void save_model();

    };

}
