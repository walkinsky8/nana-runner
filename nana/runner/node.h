// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/list_map.h>
#include <nana/runner/list_multimap.h>

namespace nana::runner
{
    class node
    {
        string type_;

        list_map<string, string> attrs_;

        list_multimap<string, node> children_;

        string value_;

    public:
        node& type(string _type)
        {
            type_ = _type;
            return *this;
        }

        node& add_attr(string n, string v)
        {
            attrs_.add(n, v);
            return *this;
        }

        node& add_child(string n, node v)
        {
            children_.add(n, v);
            return *this;
        }

        node& value(string _value)
        {
            value_ = _value;
            return *this;
        }

    };

}
