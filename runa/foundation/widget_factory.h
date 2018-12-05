// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <runa/foundation/widget_cfg.h>

namespace runa {

    class widget_factory
    {
    public:
        using create_func = std::function<cfg_ptr ()>;

    private:
        std::map<string, create_func> widgets_;

    private:
        widget_factory();
        widget_factory(const widget_factory&) = delete;
        widget_factory(widget_factory&&) = delete;
        widget_factory& operator=(const widget_factory&) = delete;
        widget_factory& operator=(widget_factory&&) = delete;

    public:
        static widget_factory& instance();

        cfg_ptr create(const string& _type);

        void add(const string& _type, create_func _func);
        
        create_func get(const string& _type) const;

    };

    template<class T>
    inline void add_widget()
    {
        widget_factory::instance().add(T::type_name_(), T::new_);
    }

}
