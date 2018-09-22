// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#include "stdafx.h"

#include <nana/runner/app_base.h>

nana::runner::app* nana::runner::app::instance_{ nullptr };

nana::runner::app::app()
{
    NAR_LOG("initializing...");
    init_enums();
    init_widgets();

    instance_ = this;
}

nana::runner::app::~app()
{
    instance_ = nullptr;
}

bool nana::runner::app::search_file(const wstring& _file, wstring& _fullpath) const
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

nana::runner::cfg_ptr nana::runner::app::load_cfg(const wstring& _filename)
{
    string cfgdata;
    const string* pdata = files_.find(_filename);
    if (pdata)
        cfgdata = *pdata;
    else
    {
        wstring fullpath;
        if (!search_file(_filename, fullpath))
            return nullptr;

        if (!read_file(fullpath, cfgdata))
            throw std::invalid_argument("read cfg error: " + to_utf8(fullpath));

        files_.add(_filename, cfgdata);
    }

    cfg_ptr cfg = widget_cfg::from(cfgdata);
    if (!cfg)
        return cfg;
    NAR_LOG_NV("cfg", dump(cfg, false, 0, true));
    auto found = cfgs_.find(cfg->id_());
    if (found)
        cfg = *found;
    else
        cfgs_.add(cfg->id_(), cfg);
    return cfg;
}

nana::runner::cfg_ptr nana::runner::app::get_cfg(const string& _type) const
{
    const cfg_ptr* p = cfgs_.find(_type);
    if (!p)
        throw std::invalid_argument(string{ "invalid view " } +_type);
    return *p;
}

void nana::runner::app::load_cfgs(const wchar_t* _cmdline)
{
    args_.init(_cmdline);

    for (auto& filename : args_.arguments())
    {
        load_cfg(filename);
    }
}

void nana::runner::app::run(const wchar_t* _cmdline)
{
    load_cfgs(_cmdline);

    on_init();
                           
    NAR_LOG("enter loop...");
    exec();
    NAR_LOG("leave.");
}
