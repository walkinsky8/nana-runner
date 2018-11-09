// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_view.h>

#include <nana/runner/app_base.h>

#include <nana/gui/filebox.hpp>

void nana::runner::sample::editor_view::init()
{
    folder_ << app::filepaths();
    folder_.option(0);
    load();

    file_.events().selected([&] { load(); });

    choose_dir_.events().click(std::bind(&self::choose_dir, this));
    open_file_.events().click(std::bind(&self::open_file, this));

    load_.events().click([&] { load(); });
    save_.events().click([&] { save(); });
    run_.events().click([&] { run(); });
    quit_.events().click([&] { close(); });

    form_.events().destroy([&] {
        close_current();
        app::quit();
    });
}

void nana::runner::sample::editor_view::on_setup(std::function<void()> _f)
{
    setup_.events().click([this, _f] { _f(); });
}

void nana::runner::sample::editor_view::choose_dir()
{
    nana::folderbox fb{ nullptr, folder_.caption() };
    auto dir = fb.show();
    if (dir.has_value())
    {
        string d = dir.value().string();
        folder_ << d;
        fs::directory_iterator di{ d }, end;
        file_.clear();
        for (; di != end; ++di)
        {
            fs::path const& p = *di;
            if (p.extension() == ".nar")
            {
                NAR_LOG_DEBUG(p.filename());
                file_.push_back(p.filename().string());
            }
        }
    }
}

void nana::runner::sample::editor_view::open_file()
{
    nana::filebox fb{ true };
    fb.init_path(folder_.caption());
    fb.init_file(file_.caption());
    fb.add_filter("Nana Cfg File (*.nar)", "*.nar");
    fb.add_filter("Any File (*.*)", "*.*");
    if (fb.show())
    {
        folder_ << fb.path();
        file_ << fs::path{ fb.file() }.filename();
        load();
    }
}

void nana::runner::sample::editor_view::load()
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
        NAR_LOG("loaded " << full << " = \n" << fbuf);
    }
}

void nana::runner::sample::editor_view::save()
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
        NAR_LOG("saved " << full << " = \n" << fbuf);
    }
}

void nana::runner::sample::editor_view::run()
{
    log_thread::instance().pause();
    wstring fname;
    string fbuf;
    file_ >> fname;
    filebuf_ >> fbuf;
    //write_file(fname, fbuf);
    NAR_LOG("run nar cfg = " << fbuf);
    NAR_LOG("run nar file = " << fname);
    close_current();
    curr_cfg_ = widget_cfg::from(fbuf);
    current_ = view_obj::make_view(*curr_cfg_, nullptr);
    if (current_)
        current_->show();
    log_thread::instance().resume();
}

void nana::runner::sample::editor_view::close_current()
{
    if (current_)
    {
        current_->close();
        current_ = nullptr;
        curr_cfg_ = nullptr;
    }
}

