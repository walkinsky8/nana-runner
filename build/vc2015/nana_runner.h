// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>
#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

namespace nana::runner
{
    class app
    {
        wstring cmdline_;
        std::vector<wstring> args_;
        std::vector<cfg_ptr> cfgs_;

    public:
        app(const wchar_t* _cmdline)
            : cmdline_{ _cmdline }
        {
            NAR_LOG("initializing...");
            init_enums();
            init_widgets();

            string u8s;
            u8s << cmdline_;
            parser ps{ u8s, true };
            ps >> args_;

            auto close_all_func = [this] { close_all(); };

            for (auto& filename : args_)
            {
                cfg_ptr p = widget_cfg::from_file(filename);
                NAR_LOG_NV("cfg", dump(p, false, 0, true));
                p->close_all_(close_all_func);
                cfgs_.push_back(p);
            }
        }

        void close_all()
        {
            for (auto i : cfgs_)
                i->close();
        }

        void run()
        {
            NAR_LOG("enter loop...");
            exec();
            NAR_LOG("leave.");
        }

    };

}
