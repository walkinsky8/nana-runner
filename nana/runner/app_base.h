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

        static void quit();

        void run(const wchar_t* _cmdline);

        bool search_file(const wstring& _filename, wstring& _fullpath) const;

        string load_file(const wstring& _filename) const;

        cfg_ptr load_cfg(const wstring& _filename);

        cfg_ptr create_cfg(const string& _cfgdata);

        cfg_ptr get_cfg(const string& _id) const;

        static view_ptr create_view(const string& _cfg);

        view_ptr load_view(const wstring& _filename);

        static view_ptr get_view(const wstring& _filename)
        {
            return instance().load_view(_filename);
        }

        static wstring find_file(const wstring& _filename)
        {
            wstring fullpath;
            instance().search_file(_filename, fullpath);
            return fullpath;
        }
        static wstring find_file(const string& _filename)
        {
            return find_file(to_wstring(_filename));
        }
        static nana::paint::image create_image(const string& _filename)
        {
            return image{ find_file(_filename) };
        }

    protected:
        virtual void on_init() { }

        virtual void on_fini() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
