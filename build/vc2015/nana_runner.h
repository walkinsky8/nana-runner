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
            initialize();

            view_ = widget_cfg::from_file(cmdline_);
            
            view_->make_widgets(form_);
            
            _View view(*view_, form_);
            
            form_.show();
            
            exec();
        }

    };

}
