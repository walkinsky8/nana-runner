// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/view_cfg.h>

namespace nana::runner
{
    template<class _View>
    class app
    {
        wstring cmdline_;
        view_cfg viewcfg_;
        form form_;

    public:
        app(const wchar_t* _cmdline)
            : cmdline_{ _cmdline }
        {
            initialize();

            viewcfg_.from_file(cmdline_);
            
            viewcfg_.make_widgets(form_);
            
            _View view(viewcfg_, form_);
            
            make_form(form_, viewcfg_);
            
            form_.show();
            
            exec();
        }

    };

}
