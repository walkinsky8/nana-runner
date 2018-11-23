// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_view_impl.h>

#include <nana/runner/app_base.h>

#include <nana/gui/filebox.hpp>

void runa::sample::editor_view_impl::init()
{
    folder_ << app::filepaths();
    folder_.option(0);
    on_load();
    init_files();

    file_.events().selected([&] { on_load(); });

    choose_dir_.events().click([&] { on_choose_dir(); });
    open_file_.events().click([&] { on_open_file(); });

    load_.events().click([&] { on_load(); });
    save_.events().click([&] { on_save(); });
    run_.events().click([&] { on_run(); });
    quit_.events().click([&] { close(); });

    form_.events().destroy( app::quit );
}

void runa::sample::editor_view_impl::on_choose_dir()
{
    nana::folderbox fb{ nullptr, folder_.caption() };
    auto dir = fb.show();
    if (dir.has_value())
    {
        string d = dir.value().string();
        folder_ << d;
        NAR_LOG_VAR(folder_);
        init_files();
    }
}

void runa::sample::editor_view_impl::init_files()
{
    file_.clear();
    fs::directory_iterator di{ folder_.caption() }, end;
    for (; di != end; ++di)
    {
        fs::path const& p = *di;
        if (p.extension() == ".nar")
        {
            NAR_LOG_VAR(p.filename());
            file_.push_back(p.filename().string());
        }
    }
}

void runa::sample::editor_view_impl::on_open_file()
{
    nana::filebox fb{ true };
    fb.init_path(folder_.caption());
    fb.init_file(file_.caption());
    fb.add_filter("Nana Cfg File (*.nar)", "*.nar");
    fb.add_filter("Any File (*.*)", "*.*");
    if (fb.show())
    {
        NAR_LOG_VAR(fb.file());
        folder_ << fb.path();
        file_ << fs::path{ fb.file() }.filename();
        on_load();
    }
}

void runa::sample::editor_view_impl::on_load()
{
    wstring dir;
    wstring fname;
    folder_ >> dir;
    file_ >> fname;
    if (!fname.empty())
    {
        string fbuf;
        fs::path p{ dir }; p /= fname;
        wstring full = p.wstring();
        bool found = false;
        if (fs::exists(p))
            found = read_file(full, fbuf);
        if (!found)
            fbuf = app::instance().load_file(fname, &full);
        p = full;
        folder_ << p.parent_path().string();
        file_ << p.filename();
        filebuf_ << fbuf;
        NAR_LOG_VAR(full);
    }
}

void runa::sample::editor_view_impl::on_save()
{
    wstring dir;
    wstring fname;
    string fbuf;
    folder_ >> dir;
    file_ >> fname;
    filebuf_ >> fbuf;
    if (!fname.empty() && !fbuf.empty())
    {
        wstring full = fs::path{ dir } / fname;
        write_file(full, fbuf);
        NAR_LOG_VAR(full);
    }
}

void runa::sample::editor_view_impl::on_run()
{
    log_thread::instance().pause();
    //save();
    NAR_LOG_VAR(file_);
    string fbuf;
    filebuf_ >> fbuf;
    //NAR_LOG_VAR(fbuf);
    close_current();
    try {
        curr_cfg_ = widget_cfg::from(fbuf);
        if (curr_cfg_)
        {
            curr_run_ = view_obj::make_view(*curr_cfg_, nullptr);
            if (curr_run_)
                curr_run_->show();
        }
    }
    catch (std::exception& e) {
        NAR_LOG_EXCPT(e);
    }
    log_thread::instance().resume();
}

void runa::sample::editor_view_impl::on_fini()
{
    close_current();
}

void runa::sample::editor_view_impl::close_current()
{
    close_view(curr_run_);
    curr_run_ = nullptr;
}

