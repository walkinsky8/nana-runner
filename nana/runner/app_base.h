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

        std::vector<view_ptr> initial_views_;

    public:
        app();
        ~app();

        static app& instance() { return *instance_; }

        static void close_all();

        void run(const wchar_t* _cmdline);

        bool search_file(const wstring& _filename, wstring& _fullpath) const;

        string load_file(const wstring& _filename) const;

        cfg_ptr load_cfg(const wstring& _filename);

        cfg_ptr get_cfg(const string& _id) const;

		view_ptr load_view(const wstring& _filename);

        static view_ptr get_view(const wstring& _filename)
        {
            return instance().load_view(_filename);
        }

        static wstring find_file(const string& _filename)
        {
            wstring fullpath;
            instance().search_file(to_wstring(_filename), fullpath);
            return fullpath;
        }
        static wstring find_file(const wstring& _filename)
        {
            wstring fullpath;
            instance().search_file(_filename, fullpath);
            return fullpath;
        }

    protected:
        virtual void on_init() { }

        virtual void on_fini() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
