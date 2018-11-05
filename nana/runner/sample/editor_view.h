// Created by walkinsky(lyh6188@hotmail.com), 2018/02/09
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/categorize_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class editor : public view_obj
    {
    public:
        static pcstr type_name_() { return "editor"; }
        static view_ptr new_(widget_cfg& _cfg, window _parent) { return std::make_shared<editor>(_cfg, _parent); }

    public:
        form& form_;

        textbox& filename_;

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
            , filename_{ wnd<textbox>("filename") }
            , filebuf_{ wnd<textbox>("filebuf") }
            , load_{ wnd<button>("cmd.load") }
            , save_{ wnd<button>("cmd.save") }
            , run_{ wnd<button>("cmd.run") }
            , setup_{ wnd<button>("cmd.setup") }
            , quit_{ wnd<button>("cmd.close") }
        {
            //filename_ << cfg().fullpath_();
            load();

            load_.events().click([this] { load(); });
            save_.events().click([this] { save(); });
            run_.events().click([this] { run(); });
            quit_.events().click([this] { close(); });

            form_.events().destroy([this] {
                close_current();
                app::quit();
            });
        }

        void on_setup(std::function<void()> _f)
        {
            setup_.events().click([this, _f] { _f(); });
        }

    private:
        void load()
        {
            wstring fname;
            filename_ >> fname;
            if (!fname.empty())
            {
                string fbuf = app::instance().load_file(fname);
                filebuf_ << fbuf;
                NAR_LOG("loaded = " << fbuf);
            }
        }

        void save()
        {
            wstring fname;
            filename_ >> fname;
            string fbuf;
            filebuf_ >> fbuf;
            if (!fname.empty() && !fbuf.empty())
            {
                write_file(fname, fbuf);
                NAR_LOG("saved = " << fbuf);
            }
        }

        void run()
        {
            log_thread::instance().pause();
            wstring fname;
            filename_ >> fname;
            string fbuf;
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
