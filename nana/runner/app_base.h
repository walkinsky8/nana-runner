// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/base_types.h>

#include <nana/runner/widget_cfg.h>
#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

namespace nana::runner
{
    class app_base
    {
        cmdargs args_;

        list_multimap<string, cfg_ptr> cfgs_;

    public:
        virtual ~app_base() = default;
        app_base();

        template<class T>
        T* get_view() const
        {
            const cfg_ptr* p = cfgs_.find(T::type_name_());
            if (!p)
                throw std::invalid_argument(string{ "invalid view " } +T::type_name_());
            return dynamic_cast<T*>((*p)->view_().get());
        }

        void run(const wchar_t* _cmdline);

    protected:
        virtual void init_views() { }

        virtual void init_logic() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
