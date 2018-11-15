// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/app_base.h>

nana::runner::app* nana::runner::app::instance_{ nullptr };

nana::runner::app::app()
{
    if (instance_ != nullptr)
        throw std::invalid_argument("app instance should not be more than one");

    log_thread::instance().start();

    NAR_LOG("initializing...");
    init_enums();
    init_widgets();

    instance_ = this;
}

nana::runner::app::~app()
{
    log_thread::instance().stop();
    instance_ = nullptr;
}

bool nana::runner::app::search_file(const wstring& _file, wstring& _fullpath) const
{
    fs::path p{ _file };
    if (fs::exists(p) && p.is_absolute())
    {
        _fullpath = _file;
        return true;
    }

    for (auto& p : paths_)
    {
        fs::path fullpath{ p };
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

nana::runner::string nana::runner::app::load_file(const wstring& _filename, wstring* _fullpath) const
{
    wstring fullpath;
    if (!search_file(_filename, fullpath))
        fullpath = _filename;
    else if (_fullpath)
        *_fullpath = fullpath;

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

    cfg_ptr cfg = create_cfg(cfgdata);
    if (cfg)
    {
    }
    return cfg;
}

nana::runner::cfg_ptr nana::runner::app::create_cfg(const string& cfgdata)
{
    cfg_ptr cfg = widget_cfg::from(cfgdata);
    if (!cfg)
        return cfg;

    //NAR_LOG_NV("cfg", dump(cfg, false, 0, true));
    NAR_LOG_VAR(cfg->get_caption());
    
    auto found = cfgs_.find(cfg->id_());
    if (found)
        cfg = *found;
	else
	{
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

nana::runner::cfg_ptr nana::runner::app::find_cfg(const string& _type) const
{
    const cfg_ptr* p = cfgs_.find(_type);
    if (!p)
        return nullptr;
    return *p;
}

nana::runner::view_ptr nana::runner::app::create_view_(const string& _cfg)
{
    cfg_ptr cfg = create_cfg(_cfg);
    if (cfg)
    {
        view_ptr p = view_obj::make_view(*cfg, nullptr);
        if (p)
        {
            p->show();
            initial_views_.push_back(p);
        }
        return p;
    }
    return nullptr;

}

nana::runner::view_ptr nana::runner::app::load_view_(const wstring& _filename)
{
	cfg_ptr cfg = load_cfg(_filename);
	if (cfg)
	{
		return view_obj::make_view(*cfg, nullptr);
	}
	return nullptr;
}

void nana::runner::app::load_cfgs(const wchar_t* _cmdline)
{
    args_.init(_cmdline);

    auto range = args_.options(L"path");
    for (auto p = range.first; p != range.second; ++p)
    {
        fs::path fullpath{ (*p).second };
        paths_.push_back(fullpath.u8string());
    }

    for (auto& filename : args_.arguments())
    {
        load_cfg(filename);
    }
}

void nana::runner::app::quit()
{
    instance().close();
}

void nana::runner::app::close()
{
    for (auto& v : initial_views_)
        v->close();

    on_fini();
}

void nana::runner::app::run(const wchar_t* _cmdline)
{
    load_cfgs(_cmdline);

    load_cfg(L"generic.nar");
    add_view<generic_view>();

    if (args_.arguments().empty())
        on_init();
    else
    for (auto& filename : args_.arguments())
    {
        auto& v = load_view_(filename);
        if (v)
        {
            initial_views_.push_back(v);
            v->show();
        }
    }

    NAR_LOG("enter exec...");
    exec();
    NAR_LOG("leave exec.");

    // called in quit().
    //on_fini();
}

#endif

