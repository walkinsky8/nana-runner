/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/01/15
#pragma once

#include <runa/base/object.h>

#include <runa/foundation/widget_base.h>

#define NAR_DEFINE_WIDGET(_class, _super) \
        private: \
            using super = _super; \
            using self = _class##_cfg/*user_defined*/; \
        public: \
            using ui_type = runa::_class/*user_defined*/; \
            static runa::pcstr type_name_() { return #_class; } \
            static runa::cfg_ptr new_() { return std::make_shared<self>(); } \
        public: \
            runa::string type_name() const override { return type_name_(); } \
            runa::dumper& dump(runa::dumper& _d) const override { return runa::codec(_d, const_cast<self&>(*this)); } \
            void parse(const runa::parser& _p) override { runa::codec(const_cast<runa::parser&>(_p), *this); } \
        private: \
        /**/

namespace runa {

    class widget_cfg;
    using cfg_ptr = ptr<widget_cfg>;

    using nana::paint::image;
    using nana::widget;
    using nana::window;

    class view_obj;

    class widget_cfg : public object
    {
        NAR_FIELD(id, id);
        NAR_FIELD(string, caption);
        NAR_FIELD(string, tooltip);
        NAR_FIELD(string, div);
        NAR_FIELD(string, bgcolor);
        NAR_FIELD(string, fgcolor);
        NAR_FIELD(optional<point>, pos);
        NAR_FIELD(optional<size>, size);
        NAR_FIELD(optional<cursor>, cursor);
        NAR_FIELD(optional<font>, typeface);
        NAR_FIELD(optional<bool>, enabled);
        NAR_FIELD(optional<bool>, visible);
        NAR_FIELD(optional<bool>, borderless);
        NAR_FIELD(std::vector<cfg_ptr>, children);

        widget_cfg* m_parent{ nullptr };

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            //super::traverse(_s);
            NAR_CODEC(_s, id);
            NAR_CODEC(_s, caption);
            NAR_CODEC(_s, tooltip);
            NAR_CODEC(_s, div);
            NAR_CODEC(_s, bgcolor);
            NAR_CODEC(_s, fgcolor);
            NAR_CODEC(_s, pos);
            NAR_CODEC(_s, size);
            NAR_CODEC(_s, cursor);
            NAR_CODEC(_s, typeface);
            NAR_CODEC(_s, enabled);
            NAR_CODEC(_s, visible);
            NAR_CODEC(_s, borderless);
            NAR_CODEC_UNNAMED(_s, children);
        }

    public:
        virtual wnd_ptr create_wnd(window _parent, bool _visible) const = 0;

        virtual void init_widget(widget& _w, view_obj* _root_view) const;

        virtual bool has_child_div() const { return false; }

        virtual bool has_ui_widget() const { return true; }

        virtual void make_extra_div(string& _div) const { }

        virtual point get_pos(size) const;

        static cfg_ptr from(string const& _cfg);

        static cfg_ptr get_generic();

        id id_path() const;
        id get_id_path(bool _self_node) const;

		widget_cfg* get_parent() const { return m_parent; }
		void set_parent(widget_cfg* _parent) { m_parent = _parent; }

        void reset_all_parent(widget_cfg* _parent);

        string make_div() const { string s; make_div(s); return s; }
        void make_div(string& _div) const;

        string get_caption() const;

        const string& get_bgcolor() const;
        const string& get_fgcolor() const;
        const optional<cursor>& get_cursor() const;
        const optional<font>& get_typeface() const;

	};
    inline std::ostream& operator<<(std::ostream& _os, const widget_cfg& _v)
    {
        return _os << dump(_v, false, 0, true);
    }
    inline dumper& operator<<(dumper& _d, const widget_cfg& _v)
    {
        return _v.dump(_d);
    }
    inline void operator>>(const parser& _p, widget_cfg& _v)
    {
        _v.parse(_p);
    }

    void operator >> (const parser& _is, cfg_ptr& _v);

}
