// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/widget_all.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/controller_base.h>

#include <nana/runner/generic_view.h>

namespace nana::runner
{
    class app : public object
    {
        static app* instance_;

        cmdargs args_;

        list_map<wstring, string> files_; // file name ==> content

        list_map<string, cfg_ptr> cfgs_; // cfg id ==> ptr

    public:
        app();
        ~app();

        static app& instance() { return *instance_; }

        static view_ptr get_view(const wstring& _filename)
        {
            return instance().load_view(_filename);
        }

        static void close_all()
        {
            instance().on_fini();
        }

        void run(const wchar_t* _cmdline);

        bool search_file(const wstring& _file, wstring& _fullpath) const;

        cfg_ptr load_cfg(const wstring& _filename);

        cfg_ptr get_cfg(const string& _id) const;

		view_ptr load_view(const wstring& _filename);

	protected:
        virtual void on_init() { }

        virtual void on_fini() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
