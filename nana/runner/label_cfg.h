// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    class label_cfg : public widget_cfg
    {
    public:
        using super = widget_cfg;
        using self = label_cfg;
        using ui_type = nana::label;
        static pcstr type_name_() { return "label"; }

    private:
        NAR_FIELD(optional<bool>, transparent);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, transparent);
        }

        dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); }

        void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); }

        string type_name() const override { return type_name_(); }

        static view_ptr new_() { return std::make_shared<self>(); }
        view_ptr new_obj() const override { return new_(); }

        static wnd_ptr create_widget_(window p, bool v) { return std::make_shared<ui_type>(p, v); }
        wnd_ptr create_widget(window p, bool v) const override { return create_widget_(p, v); }

        void init_widget(widget& _w) const override;

    };

}
