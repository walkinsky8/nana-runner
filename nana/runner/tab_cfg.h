// Created by walkinsky(lyh6188@hotmail.com), 2018/10/19
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/panel.hpp>

namespace nana::runner {

    using tab_ui = nana::panel<true>;

    class tab : public tab_ui
    {
        using super = tab_ui;

        std::unique_ptr<place> place_;

    public:
        tab(window owner, bool visible);

        place & get_place();
        void div(const char* div_text);
        place::field_reference operator[](const char* field_name);
        void collocate() noexcept;

    };

    class tab_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(tab, widget_cfg);
        NAR_FIELD(string, tab_bgcolor);
        NAR_FIELD(string, tab_fgcolor);
        NAR_FIELD(string, tab_image);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, tab_bgcolor);
            NAR_CODEC(_s, tab_fgcolor);
            NAR_CODEC(_s, tab_image);
        }

        wnd_ptr create_wnd(window p, bool v) const override;

        void init_widget(widget& _w, view_obj* _root_view) const override;

        bool has_child_div() const override { return true; }

    };

}
