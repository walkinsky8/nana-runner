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
        cfg_ptr cfg_;
        view_ptr view_;

    public:
        app(const wchar_t* _cmdline)
            : cmdline_{ _cmdline }
        {
            NAR_LOG("initializing...");
            init_enums();
            init_widgets();

            NAR_LOG("read cfg...");
            cfg_ = widget_cfg::from_file(cmdline_);
            NAR_LOG_NV("cfg_", dump(cfg_, false, 0, true));
            
            NAR_LOG("create view...");
            view_ = create_view(*cfg_);
            
            NAR_LOG("enter loop...");
            exec();

            NAR_LOG("leave.");
        }

    };

}
