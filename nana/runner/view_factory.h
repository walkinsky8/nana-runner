// Created by walkinsky(lyh6188@hotmail.com), 2018/01/21
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/view_base.h>

namespace nana::runner {

    class view_factory
    {
    public:
        using create_func = std::function<view_ptr (widget_cfg&, window)>;

    private:
        std::map<string, create_func> widgets_;

    private:
        view_factory();
        view_factory(const view_factory&) = delete;
        view_factory(view_factory&&) = delete;
        view_factory& operator=(const view_factory&) = delete;
        view_factory& operator=(view_factory&&) = delete;

    public:
        static view_factory& instance();

        view_ptr create(const string& _type, widget_cfg& _cfg, window _parent);

        void add(const string& _type, create_func _func);
        
        create_func get(const string& _type) const;

    };

    template<class T>
    inline void add_view()
    {
        view_factory::instance().add(T::type_name_(), T::new_);
    }

    inline view_ptr create_view(widget_cfg& _cfg, window _parent)
    {
        return view_factory::instance().create(_cfg.id_path(), _cfg, _parent);
    }

}
