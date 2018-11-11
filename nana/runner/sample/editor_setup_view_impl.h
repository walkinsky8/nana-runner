// Created by walkinsky(lyh6188@hotmail.com), 2018/11/11
#pragma once

#include <nana/runner/sample/editor_setup_view.h>

#include <nana/runner/sample/editor_setup_model.h>

namespace nana::runner::sample {

    class editor_setup_view_impl: public editor_setup_view
    {
        NAR_DEFINE_VIEW_IMPL(editor_setup);

        NAR_FIELD(editor_setup_model, model);

        widget* target_{};

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_target(widget* _target);

    private:
        void init();

        void init_model();

        void update_model();

        void load_model();

        void save_model();

        void load_widget(const widget& _w);

        void save_widget(widget& _w) const;

        widget& target()
        {
            return target_ ? *target_ : sample_;
        }

    };

}
