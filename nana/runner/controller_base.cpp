// Created by walkinsky(lyh6188@hotmail.com), 2018/01/30
#include "stdafx.h"

#include <nana/runner/controller_base.h>

nana::runner::controller_obj::controller_obj()
{
    NAR_LOG("initializing...");
    init_enums();
    init_widgets();
}

bool nana::runner::controller_obj::find_file(const wstring& _file, wstring& _fullpath)
{
    auto paths = args_.options(L"path");
    for (auto p = paths.first; p != paths.second; ++p)
    {
        fs::path fullpath{ (*p).second };
        fullpath /= _file;
        if (fs::exists(fullpath))
        {
            _fullpath = fullpath;
            return true;
        }
    }
    return false;
}

void nana::runner::controller_obj::close_all()
{
    for (auto i : cfgs_)
    {
        i->close();
    }
}

void nana::runner::controller_obj::load_cfgs(const wchar_t* _cmdline)
{
    args_.init(_cmdline);

    auto close_all_func = [this] { close_all(); };

    for (auto& filename : args_.arguments())
    {
        wstring fullpath;
        if (find_file(filename, fullpath))
        {
            cfg_ptr cfg = widget_cfg::from_file(fullpath);
            NAR_LOG_NV("cfg", dump(cfg, false, 0, true));
            cfg->close_all_(close_all_func);
            cfgs_.add(cfg->id_(), cfg);
        }
    }
}

void nana::runner::controller_obj::run(const wchar_t* _cmdline)
{
    init_views();

    load_cfgs(_cmdline);

    init_logic();

    NAR_LOG("enter loop...");
    exec();
    NAR_LOG("leave.");
}
