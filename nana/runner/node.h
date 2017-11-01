// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/istr.h>
#include <nana/runner/dumper.h>
#include <nana/runner/list_map.h>
#include <nana/runner/list_multimap.h>

namespace nana::runner
{
    class node
    {
        string name_;
        string type_;
        string value_;
        list_map<string, node> children_;

    public:
        node(string _name = {}, string _type = {}, string _value = {})
            : name_{ _name }, type_{ _type }, value_{ _value }
        {
        }

        node& clear()
        {
            name_.clear();
            type_.clear();
            value_.clear();
            children_.clear();
        }

        node& name(istr _name)
        {
            _name >> name_;
            return *this;
        }

        string const& name() const
        {
            return name_;
        }

        node& type(istr _type)
        {
            _type >> type_;
            return *this;
        }

        string const& type() const
        {
            return type_;
        }

        node& value(istr _value)
        {
            _value >> value_;
            return *this;
        }

        string const& value() const
        {
            return value_;
        }

        const list_map<string, node>& children() const
        {
            return children_;
        }

        bool simple() const
        {
            return children_.empty();
        }

        node& add_attr(string _name, string _value)
        {
            children_.add(_name, { _name, {}, _value });
            return *this;
        }

        node& add_child(string _name, node _child)
        {
            children_.add(_name, _child);
            return *this;
        }

        string const& type_name() const
        {
            return type_;
        }

        void traverse(dumper& _s);

    };
    inline dumper& operator<<(dumper& _d, const node& _v)
    {
        return codec(_d, const_cast<node&>(_v));
    }

}
