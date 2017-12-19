// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner {

    using create_func = std::function<widget_cfg* ()>;
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

        widget_cfg* create(const string& _type);

        void add(const string& _type, create_func _func);
        
        create_func get(const string& _type) const;

    };

    template<>
    struct new_<widget_cfg>
    {
        using new_func = std::function<widget_cfg* (string)>;

        new_func operator()() const
        {
            return [](string const& _type) {
                return widget_factory::instance().create(_type);
            };
        }

    };

}
