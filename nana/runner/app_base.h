// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/base_types.h>

#include <nana/runner/widget_cfg.h>
#include <nana/runner/widget_factory.h>
#include <nana/runner/view_factory.h>

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

        void run(const wchar_t* _cmdline);

        bool search_file(const wstring& _file, wstring& _fullpath) const;

        cfg_ptr load_cfg(const wstring& _filename);

        cfg_ptr get_cfg(const string& _type) const;

    protected:
        virtual void on_init() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
