// Created by walkinsky(lyh6188@hotmail.com), 2018/01/18
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/categorize.hpp>

namespace nana::runner {

    using categorize = nana::categorize<string>;

    class categorize_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(categorize, widget_cfg);

        //NAR_FIELD(string, splitstr); // no effect, maybe nana has bug for categorize::tree_wrapper::path(string)

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            //NAR_CODEC(_s, splitstr);
        }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
