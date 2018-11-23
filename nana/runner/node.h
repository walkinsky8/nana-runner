// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/base_types.h>

namespace runa
{
    class dumper;

    class node
    {
        string name_;
        string type_;
        string value_;
        typedef list_multimap<string, node> _Children;
        _Children children_;

    public:
        node(string _name = {}, string _type = {}, string _value = {})
            : name_{ _name }, type_{ _type }, value_{ _value }
        {
        }

        void clear();

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

        const _Children& children() const
        {
            return children_;
        }

        const node* child(const string& _name) const
        {
            return children_.find(_name);
        }

        _Children::_Range child_equal(const string& _name) const
        {
            return children_.equal_range(_name);
        }

        bool simple() const
        {
            return children_.empty();
        }

        size_t num_of_children() const
        {
            return children_.size();
        }

        bool valueIsEmpty() const
        {
            return value_.empty() && children_.empty();
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

}
