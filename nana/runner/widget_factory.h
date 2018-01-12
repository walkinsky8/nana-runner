// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    using create_func = std::function<view_ptr ()>;

    class widget_factory
    {
        std::map<string, create_func> widgets_;

        widget_factory();
        widget_factory(const widget_factory&) = delete;
        widget_factory(widget_factory&&) = delete;
        widget_factory& operator=(const widget_factory&) = delete;
        widget_factory& operator=(widget_factory&&) = delete;

    public:
        static widget_factory& instance();

        view_ptr create(const string& _type);

        void add(const string& _type, create_func _func);
        
        create_func get(const string& _type) const;

    };

}
