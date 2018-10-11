// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_base.h>

#define NAR_DEFINE_WIDGET(_class, _super) \
        private: \
            using super = _super; \
            using self = _class##_cfg/*user_defined*/; \
        public: \
            using ui_type = nana::runner::##_class/*user_defined*/; \
            static nana::runner::pcstr type_name_() { return #_class; } \
            static nana::runner::cfg_ptr new_() { return std::make_shared<self>(); } \
        public: \
            nana::runner::string type_name() const override { return type_name_(); } \
            nana::runner::cfg_ptr new_obj() const override { return new_(); } \
            nana::runner::wnd_ptr create_wnd(nana::window p, bool v) const override { return create_wnd_/*user_defined*/(p, v); } \
            nana::runner::dumper& dump(nana::runner::dumper& _d) const override { return nana::runner::codec(_d, const_cast<self&>(*this)); } \
            void parse(const nana::runner::parser& _p) override { nana::runner::codec(const_cast<nana::runner::parser&>(_p), *this); } \
        private: \
        /**/

namespace nana::runner {

    class widget_cfg;
    using cfg_ptr = ptr<widget_cfg>;

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
        NAR_FIELD(std::vector<cfg_ptr>, children);

		widget_cfg* m_parent{ nullptr };
		NAR_FIELD(wstring, fullpath);

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
            NAR_CODEC_UNNAMED(_s, children);
        }

    public:
        virtual string type_name() const = 0;

        virtual cfg_ptr new_obj() const = 0;

        virtual dumper& dump(dumper& _d) const = 0;

        virtual void parse(const parser& _p) = 0;

        virtual wnd_ptr create_wnd(window _parent, bool _visible) const = 0;

        virtual void init_widget(widget& _w) const;

        virtual void on_init_view(widget& _w, const std::map<id, wnd_ptr>& _widgets) const { }

        virtual point get_pos() const;

		static cfg_ptr from(string const& _cfg);

		id id_path() const
        {
            if (!m_parent || id_().empty())
                return id_();
            return m_parent->id_path() / id_();
        }

		widget_cfg* get_parent() const { return m_parent; }
		void set_parent(widget_cfg* _parent) { m_parent = _parent; }

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

    template<> struct dumpable<widget_cfg> { static constexpr bool value = true; };

    void operator >> (const parser& _is, cfg_ptr& _v);

}
