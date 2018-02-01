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
    args_.init(_cmdline);

    auto close_all_func = [this] {
        for (auto i : cfgs_)
        {
            i->close();
        }
    };

    auto paths = args_.options(L"path");
    for (auto& filename : args_.arguments())
    {
        for (auto p = paths.first; p != paths.second; ++p)
        {
            fs::path fullpath{ (*p).second };
            fullpath /= filename;
            if (fs::exists(fullpath))
            {
                cfg_ptr cfg = widget_cfg::from_file(fullpath);
                NAR_LOG_NV("cfg", dump(cfg, false, 0, true));
                cfg->close_all_(close_all_func);
                cfgs_.add(cfg->id_(), cfg);
            }
        }
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
