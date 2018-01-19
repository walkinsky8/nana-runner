// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/view_base.h>

#define NAR_DEFINE_WIDGET(_class, _super) \
        public: \
            using super = _super; \
            using self = _class##_cfg; \
            using ui_type = _class##_ui; \
            static pcstr type_name_() { return #_class; } \
        public: \
            static view_ptr new_() { return std::make_shared<self>(); } \
            string type_name() const override { return type_name_(); } \
            view_ptr new_obj() const override { return new_(); } \
            wnd_ptr create_widget(window p, bool v) const override { return create_widget_(p, v); } \
            dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); } \
            void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); } \
        private:

namespace nana::runner {

    class widget_cfg;
    using view_ptr = std::shared_ptr<widget_cfg>;
    using wnd_ptr = std::shared_ptr<widget>;

    class widget_cfg
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
        NAR_FIELD(std::vector<view_ptr>, children);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
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
            NAR_CODEC(_s, children);
        }

    private:
        widget_cfg* m_parent{ nullptr };

        // only for root(form)
        using _Widgets = std::map<id, wnd_ptr>;
        NAR_FIELD(_Widgets, widgets);

    public:
        virtual ~widget_cfg() = default;

        virtual dumper& dump(dumper& _d) const = 0;

        virtual void parse(const parser& _p) = 0;

        virtual string type_name() const = 0;

        virtual view_ptr new_obj() const = 0;

        virtual wnd_ptr create_widget(window _parent, bool _visible) const = 0;

        virtual void init_widget(widget& _w) const;

        template<class T>
        T& cast()
        {
            return dynamic_cast<T&>(*this);
        }

        template<class T>
        const T& cast() const
        {
            return dynamic_cast<const T&>(*this);
        }

        id id_name() const
        {
            if (!m_parent || id_().empty())
                return id_();
            return m_parent->id_name() / id_();
        }

        void set_parent(widget_cfg* _parent)
        {
            m_parent = _parent;
        }

        static view_ptr from_file(wstring const& _filename);

        wnd_ptr get_widget_(id _id) const;

        template<class T>
        T& wnd(id _id) const
        {
            wnd_ptr w = get_widget_(_id);
            if (!w)
                throw std::invalid_argument("no widget for " + _id.str());
            return dynamic_cast<T&>(*w);
        }

        void make_widgets(nana::widget& _root_wnd);
        void make_widgets(widget_cfg& _root, widget_cfg* _parent_cfg, nana::window _parent_wnd);

        string make_div() const
        {
            string s;
            make_div(s);
            return s;
        }
        void make_div(string& _div) const;

        string get_caption() const;

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

    template<>
    struct dumpable<widget_cfg>
    {
        static constexpr bool value = true;
    };

    void operator >> (const parser& _is, std::shared_ptr<widget_cfg>& _v);

}
