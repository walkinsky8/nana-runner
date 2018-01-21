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
            initialize();
            init_widgets();

            NAR_LOG("read cfg file...");
            cfg_ = widget_cfg::from_file(cmdline_);
            NAR_LOG_NV("view_", dump(cfg_, false, 0, true));
            
            NAR_LOG("init view...");
            view_ = view_factory::instance().create(cfg_->id_path(), *cfg_);
            
            NAR_LOG("show view.");
            view_->show();
            
            NAR_LOG("enter main loop...");
            exec();

            NAR_LOG("leave.");
        }

    };

}
