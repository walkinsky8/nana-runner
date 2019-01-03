// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#pragma once

#include <runa/foundation/color/color_view.h>

#include <runa/foundation/color/color_model.h>

namespace runa {

    class color_view_impl : public color_view
    {
        NAR_DEFINE_VIEW_IMPL(color);

        model_proxy<color_model> model_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
            init();
        }

        void set_model_proxy(model_proxy<color_model> const& _proxy);

    private:
        void init();

        void on_ok();
        void on_cancel();

        void on_color_selected();
        void on_color_text_changed();
        void on_input_changed();

        void on_chooser_type_changed();
        void on_chooser_value_changed(const color& _c);

        void load_model();
        void save_model();

        string get_string_value() const;

        color get_value() const;
        void set_value(const color& _c);

        color_mode get_chooser_type() const;

        void update_output(const color& _c);

    };

}

