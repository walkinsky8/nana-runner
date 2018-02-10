// Created by walkinsky(lyh6188@hotmail.com), 2018/02/09
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_cfg.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/categorize_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class Editor : public view_obj
    {
    public:
        static pcstr type_name_() { return "editor"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<Editor>(_cfg); }

    //private:
        form& form_;

        textbox& filename_;

        textbox& filebuf_;

        checkbox& linewrap_;
        button& load_;
        button& save_;
        button& run_;
        button& quit_;

    private:
        cfg_ptr current_;

    public:
        Editor(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ _cfg.wnd<form>() }
            , filename_{ _cfg.wnd<textbox>("filename") }
            , filebuf_{ _cfg.wnd<textbox>("filebuf") }
            , linewrap_{ _cfg.wnd<checkbox>("cmd.linewrap") }
            , load_{ _cfg.wnd<button>("cmd.load") }
            , save_{ _cfg.wnd<button>("cmd.save") }
            , run_{ _cfg.wnd<button>("cmd.run") }
            , quit_{ _cfg.wnd<button>("cmd.close") }
        {
            filename_ << cfg().fullpath_();
            load();

            linewrap_.events().checked([this] {
                filebuf_.line_wrapped(linewrap_.checked());
            });

            load_.events().click([this] { load(); });
            save_.events().click([this] { save(); });
            run_.events().click([this] { run(); });
            quit_.events().click([this] { close(); });

            form_.events().destroy([this] { close_current(); });
        }

        void load()
        {
            wstring fname;
            filename_ >> fname;
            if (!fname.empty())
            {
                string fbuf;
                read_file(fname, fbuf);
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
            wstring fname;
            filename_ >> fname;
            string fbuf;
            filebuf_ >> fbuf;
            write_file(fname, fbuf);
            NAR_LOG("run nar cfg = " << fbuf);
            NAR_LOG("run nar file = " << fname);
            close_current();
            current_ = widget_cfg::from_file(fname);
            if (current_)
                current_->show();
        }

        void close_current()
        {
            if (current_)
            {
                current_->close();
                current_ = nullptr;
            }
        }

    };

}
