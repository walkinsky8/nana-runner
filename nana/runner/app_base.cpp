// Created by walkinsky(lyh6188@hotmail.com), 2018/01/30
#include "stdafx.h"

#include <nana/runner/app_base.h>

nana::runner::app_base::app_base()
{
    NAR_LOG("initializing...");
    init_enums();
    init_widgets();
}

void nana::runner::app_base::load_cfgs(const wchar_t* _cmdline)
{
    string_split(_cmdline, args_);

    auto close_all_func = [this] {
        for (auto i : cfgs_)
        {
            i->close();
        }
    };

    for (auto& filename : args_)
    {
        cfg_ptr p = widget_cfg::from_file(filename);
        NAR_LOG_NV("cfg", dump(p, false, 0, true));
        p->close_all_(close_all_func);
        cfgs_.add(p->id_(), p);
    }
}

void nana::runner::app_base::run(const wchar_t* _cmdline)
{
    init_views();

    load_cfgs(_cmdline);

    init_logic();

    NAR_LOG("enter loop...");
    exec();
    NAR_LOG("leave.");
}
