// Created by walkinsky(lyh6188@hotmail.com), 2017/11/19
#pragma once

#include <nana/runner/base.h>

namespace nana::runner {

    template<class T>
    class object_factory
    {
        using create_func = std::function<T*()>;

        std::map<string, create_func> types_;

        widget_factory();
        widget_factory(const widget_factory&) = delete;
        widget_factory(widget_factory&&) = delete;
        widget_factory& operator=(const widget_factory&) = delete;
        widget_factory& operator=(widget_factory&&) = delete;

    public:
        static widget_factory& instance();

        static nana::widget* create_widget(const string& _type, nana::window _parent_wnd, bool _visible);

        void add(const string& _type, create_func _func);
        
        create_func get(const string& _type) const;

    };

}
