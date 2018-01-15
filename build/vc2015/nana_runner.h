// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

namespace nana::runner
{
    template<class _View>
    class app
    {
        wstring cmdline_;
        view_ptr view_;
        form form_;

    public:
        app(const wchar_t* _cmdline)
            : cmdline_{ _cmdline }
        {
            NAR_LOG("initializing...");
            initialize();

            NAR_LOG("read cfg file...");
            view_ = widget_cfg::from_file(cmdline_);
            NAR_LOG_NV("view_", dump(view_));
            
            NAR_LOG("make widgets...");
            view_->make_widgets(form_);
            
            NAR_LOG("init view...");
            _View view(*view_, form_);
            
            NAR_LOG("show form.");
            form_.show();
            
            NAR_LOG("enter main loop...");
            exec();

            NAR_LOG("leave.");
        }

    };

}
