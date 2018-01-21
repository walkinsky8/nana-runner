// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/form.hpp>

namespace nana::runner {

    using form = nana::form;

    class form_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(form, widget_cfg);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
        }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p); }

        void init_widget(widget& _w) const override;

    };

}
