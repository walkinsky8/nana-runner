/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/03/02
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/app_base.h>

#include <runa/foundation/view_factory.h>
#include <runa/foundation/controller_base.h>
#include <runa/foundation/generic_view.h>
#include <runa/foundation/color/color_view_impl.h>
#include <runa/foundation/font/font_view_impl.h>

#include <runa/widgets/widget_all.h>

runa::app* runa::app::instance_{ nullptr };

runa::app::app()
{
    if (instance_ != nullptr)
        NAR_THROW_ERROR(std::invalid_argument, "app instance should not be more than one");

    NAR_LOG("initializing...");
    init_enums();
    init_widgets();

    instance_ = this;
}

runa::app::~app()
{
    //called in run()
    //log_thread::instance().stop();
    instance_ = nullptr;
}

bool runa::app::search_file(const wstring& _file, wstring& _fullpath) const
{
    fs::path f{ _file };
    if (fs::exists(f) && f.is_absolute() && !fs::is_directory(f))
    {
        _fullpath = _file;
        return true;
    }

    for (auto& p : paths_)
    {
        fs::path fullpath{ p };
        fullpath /= _file;
        if (fs::exists(fullpath) && !fs::is_directory(fullpath))
        {
            _fullpath = fullpath;
            return true;
        }
        fullpath += ".nar";
        if (fs::exists(fullpath) && !fs::is_directory(fullpath))
        {
            _fullpath = fullpath;
            return true;
        }
    }
    return false;
}

runa::string runa::app::load_file(const wstring& _filename, wstring* _fullpath) const
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

runa::cfg_ptr runa::app::load_cfg(const wstring& _filename)
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
            NAR_THROW_ERROR(std::invalid_argument, "read cfg error: " << fullpath);

        files_.add(_filename, cfgdata);
    }

    cfg_ptr cfg = create_cfg(cfgdata);
    if (cfg)
    {
    }
    return cfg;
}

runa::cfg_ptr runa::app::create_cfg(const string& cfgdata)
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

runa::cfg_ptr runa::app::get_cfg(const string& _type) const
{
    const cfg_ptr* p = cfgs_.find(_type);
    if (!p)
        NAR_THROW_ERROR(std::invalid_argument, "invalid view " << _type);
    return *p;
}

runa::cfg_ptr runa::app::find_cfg(const string& _type) const
{
    const cfg_ptr* p = cfgs_.find(_type);
    if (!p)
        return nullptr;
    return *p;
}

runa::view_ptr runa::app::create_view_(const string& _cfg)
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

runa::view_ptr runa::app::load_view_(const wstring& _filename)
{
	cfg_ptr cfg = load_cfg(_filename);
	if (cfg)
	{
		return view_obj::make_view(*cfg, nullptr);
	}
	return nullptr;
}

runa::view_ptr runa::app::show_view_(const wstring& _filename)
{
    auto v = load_view_(_filename);
    if (v)
    {
        initial_views_.push_back(v);
        v->show();
    }
    return v;
}

void runa::app::load_cfgs(const wchar_t* _cmdline)
{
    args_.init(_cmdline);

    auto range = args_.options(L"path");
    for (auto p = range.first; p != range.second; ++p)
    {
        fs::path fullpath{ (*p).second };
        paths_.push_back(fullpath.string());
    }

    if (paths_.empty())
    {
        NAR_LOG_ERROR("Neither .nar nor -path specified in cmdline");
    }

    for (auto& filename : args_.arguments())
    {
        load_cfg(filename);
    }
}

void runa::app::quit()
{
    instance().close();
}

void runa::app::close()
{
    for (auto& v : initial_views_)
        v->close();

    on_fini();
}

void runa::app::run(const wchar_t* _cmdline)
{
    //log_thread::instance().output_directly(true);
    log_thread::instance().start();

    load_cfgs(_cmdline);

    load_cfg(L"generic.nar");
    add_view<generic_view>();

    load_cfg(L"color.nar");
    add_view<color_view_impl>();

    load_cfg(L"font.nar");
    add_view<font_view_impl>();

    try {
        if (args_.arguments().empty())
            on_init();
        else
            for (auto& filename : args_.arguments())
            {
                show_view_(filename);
            }
    }
    catch (std::exception& e) {
        NAR_LOG_EXCPT(e);
    }

    NAR_LOG("enter exec...");
    nana::exec();
    NAR_LOG("leave exec.");

    // called in quit().
    on_fini();

    log_thread::instance().stop();
}

#endif
  
