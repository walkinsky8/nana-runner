// Created by walkinsky(lyh6188@hotmail.com), 2018/11/11
#pragma once

#include <nana/runner/sample/editor_setup_view.h>

#include <nana/runner/sample/editor_setup_model.h>

#include <nana/runner/color_cntrl.h>

namespace runa::sample {

    class editor_setup_view_impl: public editor_setup_view
    {
        NAR_DEFINE_VIEW_IMPL(editor_setup);

        NAR_FIELD(editor_setup_model, model);

        widget* target_{};

        callback fn_update_{};

        color_cntrl color_setup_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_target(widget* _target);

    private:
        void init();

        void on_color_setup(combox& _c);

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

