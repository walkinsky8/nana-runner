// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/istr.h>
#include <nana/runner/optional.h>
#include <nana/runner/id.h>
#include <nana/runner/dumper.h>

namespace nana::runner {

    class view_cfg
    {
        VIO_FIELD(string, __type);

        VIO_FIELD(id, id);
        VIO_FIELD(string, caption);
        VIO_FIELD(string, string);
        VIO_FIELD(optional<bool>, bool);
        VIO_FIELD(optional<int>, int);
        VIO_FIELD(optional<float>, float);

        std::vector<view_cfg> m_children;

        view_cfg* m_parent{ nullptr };

    public:
        view_cfg()
        {}

        view_cfg(istr _id, istr _cap)
            : m_id{_id}, m_caption{_cap}
        {}

        template<class _Stream>
        void traverse(_Stream& _s)
        {
            VIO_CODEC(_s, id);
            VIO_CODEC(_s, caption);
            VIO_CODEC(_s, string);
            VIO_CODEC(_s, bool);
            VIO_CODEC(_s, int);
            VIO_CODEC(_s, float);
            VIO_CODEC(_s, children);
        }

        string type_name() const
        {
            return __type_();
        }

        string& type_name()
        {
            return __type_();
        }

        id id_name() const
        {
            if (!m_parent)
                return id_();
            return m_parent->id_name() / id_();
        }

        const std::vector<view_cfg>& children() const
        {
            return m_children;
        }

        void add(view_cfg _child)
        {
            m_children.push_back(std::move(_child));
            m_children.back().set_parent(this);
        }

        void set_parent(view_cfg* _parent)
        {
            m_parent = _parent;
        }

    };
    std::ostream& operator<<(std::ostream& _os, const view_cfg& _v)
    {
        return _os << dump(_v);
    }
    template<> struct dumpable<view_cfg>
    {
        static constexpr bool value = true;
    };

}
