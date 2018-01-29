// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>
#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

namespace nana::runner
{
    class app_base
    {
        std::vector<wstring> args_;
        list_multimap<string, cfg_ptr> cfgs_;

    public:
        virtual ~app_base() = default;
        app_base()
        {
            NAR_LOG("initializing...");
            init_enums();
            init_widgets();
        }

        template<class T>
        T* get_view() const
        {
            const cfg_ptr* p = cfgs_.find(T::type_name_());
            if (!p)
                throw std::invalid_argument(string{ "invalid view " } +T::type_name_());
            return dynamic_cast<T*>((*p)->view_().get());
        }

        void load_cfgs(const wchar_t* _cmdline)
        {
            init_views();

            auto close_all_func = [this] {
                for (auto i : cfgs_)
                {
                    i->close();
                }
            };

            string_split(_cmdline, args_);

            for (auto& filename : args_)
            {
                cfg_ptr p = widget_cfg::from_file(filename);
                NAR_LOG_NV("cfg", dump(p, false, 0, true));
                p->close_all_(close_all_func);
                cfgs_.add(p->id_(), p);
            }
        }

        void run(const wchar_t* _cmdline)
        {
            load_cfgs(_cmdline);

            init_logic();

            NAR_LOG("enter loop...");
            exec();
            NAR_LOG("leave.");
        }

        virtual void init_views()
        {
        }

        virtual void init_logic()
        {
        }

    };

}
