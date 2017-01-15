// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/dumper.h>
#include <nana/runner/id.h>

namespace nana::runner {

    class view_cfg
    {
        id id_{ "root" };
        std::string caption_{ "hello" };

        std::vector<view_cfg> children_;

        view_cfg* parent_{ nullptr };

    public:
        view_cfg() = default;
        view_cfg(id _id) :id_{ _id } {}

        template<class _Stream>
        void traverse(_Stream& _s)
        {
            _s("id", id_);
            _s("caption", caption_);
            _s("children", children_);
        }

        string type_name() const
        {
            return "view_cfg";
        }

        id id_name() const
        {
            if (!parent_)
                return id_;
            return parent_->id_name() / id_;
        }

        const std::vector<view_cfg>& children() const
        {
            return children_;
        }

        void add(view_cfg _child)
        {
            children_.push_back(std::move(_child));
            children_.back().set_parent(this);
        }

        void set_parent(view_cfg* _parent)
        {
            parent_ = _parent;
        }

    };
    std::ostream& operator<<(std::ostream& _os, const view_cfg& _v)
    {
        return _os << dump(_v);
    }
}
