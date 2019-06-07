/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/21
#pragma once

#include <runa/base/base.h>

#include <runa/foundation/widget_cfg.h>

#include <runa/foundation/view_base.h>

namespace runa {

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
