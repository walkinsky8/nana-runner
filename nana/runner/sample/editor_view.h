// Created by walkinsky(lyh6188@hotmail.com), 2018/02/09
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/button_cfg.h>

#include <nana/gui/filebox.hpp>

namespace nana::runner::sample::view {

    class editor : public view_obj
    {
        typedef editor self;
    public:
        static pcstr type_name_() { return "editor"; }
        static view_ptr new_(widget_cfg& _cfg, window _parent) { return std::make_shared<editor>(_cfg, _parent); }

    public:
        form& form_;

        combox& folder_;
        button& choose_dir_;
        combox& file_;
        button& open_file_;

        textbox& filebuf_;

        button& load_;
        button& save_;
        button& run_;
        button& setup_;
        button& quit_;

    private:
        view_ptr current_;
		cfg_ptr curr_cfg_;

    public:
        editor(widget_cfg& _cfg, window _parent)
            : view_obj{ _cfg, _parent }
            , form_{ wnd<form>() }
            , folder_{ wnd<combox>("folder.value") }
            , choose_dir_{ wnd<button>("folder.choose_dir") }
            , file_{ wnd<combox>("file.value") }
            , open_file_{ wnd<button>("file.open_file") }
            , filebuf_{ wnd<textbox>("filebuf") }
            , load_{ wnd<button>("cmd.load") }
            , save_{ wnd<button>("cmd.save") }
            , run_{ wnd<button>("cmd.run") }
            , setup_{ wnd<button>("cmd.setup") }
            , quit_{ wnd<button>("cmd.close") }
        {
            folder_ << app::filepaths();
            folder_.option(0);
            load();

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

        void on_setup(std::function<void()> _f)
        {
            setup_.events().click([this, _f] { _f(); });
        }

    private:
        void choose_dir()
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

        void open_file()
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

        void load()
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

        void save()
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

        void run()
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

        void close_current()
        {
            if (current_)
            {
                current_->close();
                current_ = nullptr;
				curr_cfg_ = nullptr;
            }
        }

    };

}
