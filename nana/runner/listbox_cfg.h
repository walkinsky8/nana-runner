// Created by walkinsky(lyh6188@hotmail.com), 2018/10/16
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/listbox.hpp>

namespace nana::runner {

    using listbox = nana::listbox;

    class listbox_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(listbox, widget_cfg);

        NAR_FIELD(optional<bool>, sortable);
        NAR_FIELD(optional<bool>, show_header);
        NAR_FIELD(std::vector<cfg_ptr>, headers);
        NAR_FIELD(std::vector<cfg_ptr>, categories);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, sortable);
            NAR_CODEC(_s, show_header);
            NAR_CODEC(_s, headers);
            NAR_CODEC(_s, categories);
        }

        wnd_ptr create_wnd(window p, bool v) const override { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w, view_obj* _root_view) const override;

    };

}
