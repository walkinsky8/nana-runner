// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/base_types.h>

#include <nana/runner/widget_cfg.h>
#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

namespace nana::runner
{
    class controller_obj;
    using ctr_ptr = std::shared_ptr<controller_obj>;

    class controller_obj : public object
    {
        cmdargs args_;

        list_multimap<string, cfg_ptr> cfgs_; 

    public:
        controller_obj();

        void run(const wchar_t* _cmdline);

        void close_all();

        bool find_file(const wstring& _file, wstring& _fullpath);

        template<class T>
        T* get_view() const
        {
            const cfg_ptr* p = cfgs_.find(T::type_name_());
            if (!p)
                throw std::invalid_argument(string{ "invalid view " } +T::type_name_());
            return dynamic_cast<T*>((*p)->view_().get());
        }

    protected:
        virtual void init_views() { }

        virtual void init_logic() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
