// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#include "stdafx.h"

#include <nana/runner/app_base.h>

nana::runner::app* nana::runner::app::instance_{ nullptr };

nana::runner::app::app()
{
    if (instance_ != nullptr)
        throw std::invalid_argument("app instance should not be more than one");

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
        fullpath += ".nar";
        if (fs::exists(fullpath))
        {
            _fullpath = fullpath;
            return true;
        }
    }
    return false;
}

nana::runner::string nana::runner::app::load_file(const wstring& _filename) const
{
    wstring fullpath;
    if (!search_file(_filename, fullpath))
        fullpath = _filename;

    string filebuf;
    read_file(fullpath, filebuf);
    return filebuf;
}

nana::runner::cfg_ptr nana::runner::app::load_cfg(const wstring& _filename)
{
	wstring fullpath;
	string cfgdata;
    const string* pdata = files_.find(_filename);
    if (pdata)
        cfgdata = *pdata;
    else
    {
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
	{
		cfg->fullpath_(fullpath);
		cfgs_.add(cfg->id_(), cfg);
	}
    return cfg;
}

nana::runner::cfg_ptr nana::runner::app::get_cfg(const string& _type) const
{
    const cfg_ptr* p = cfgs_.find(_type);
    if (!p)
        throw std::invalid_argument(string{ "invalid view " } +_type);
    return *p;
}

nana::runner::view_ptr nana::runner::app::load_view(const wstring& _filename)
{
	cfg_ptr cfg = load_cfg(_filename);
	if (cfg)
	{
		return view_obj::make_view(*cfg);
	}
	return nullptr;
}

void nana::runner::app::load_cfgs(const wchar_t* _cmdline)
{
    args_.init(_cmdline);

    for (auto& filename : args_.arguments())
    {
        load_cfg(filename);
    }
}

void nana::runner::app::close_all()
{
    for (auto& v : instance().initial_views_)
        v->close();

    instance().on_fini();
}

void nana::runner::app::run(const wchar_t* _cmdline)
{
    load_cfgs(_cmdline);

    load_cfg(L"generic.nar");
    add_view<view::Generic>();

    if (args_.arguments().empty())
        on_init();
    else
    for (auto& filename : args_.arguments())
    {
        auto& v = load_view(filename);
        if (v)
        {
            initial_views_.push_back(v);
            v->show();
        }
    }

    NAR_LOG("enter exec...");
    exec();
    NAR_LOG("leave exec.");

    // called in close_all()
    //on_fini();
}
