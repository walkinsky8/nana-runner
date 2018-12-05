// Created by walkinsky(lyh6188@hotmail.com), 2018/03/02
#pragma once

#include <runa/base/object.h>

#include <runa/foundation/view_base.h>

namespace runa
{
    class app : public object
    {
        NAR_DEFINE_OBJECT(app, object);

        static app* instance_;

        cmdargs args_;
        strings paths_;

        list_map<wstring, string> files_; // file name ==> content

        list_map<string, cfg_ptr> cfgs_; // cfg id ==> ptr

        std::vector<view_ptr> initial_views_;

    public:
        app();
        ~app();

        static app& instance() { return *instance_; }

        static void quit();

        void run(const wchar_t* _cmdline);

        void close();

        bool search_file(const wstring& _filename, wstring& _fullpath) const;

        string load_file(const wstring& _filename, wstring* _fullpath=nullptr) const;

        cfg_ptr load_cfg(const wstring& _filename);

        cfg_ptr create_cfg(const string& _cfgdata);

        cfg_ptr get_cfg(const string& _id) const; // throw exception when not found

        cfg_ptr find_cfg(const string& _id) const; // return nullptr when not found

        view_ptr create_view_(const string& _cfg);

        view_ptr load_view_(const wstring& _filename);

        view_ptr show_view_(const wstring& _filename);

        static view_ptr create_view(const string& _cfg)
        {
            return instance().create_view_(_cfg);
        }

        static view_ptr load_view(const wstring& _filename)
        {
            return instance().load_view_(_filename);
        }

        template<class _View>
        static view_ptr get_view()
        {
            string id = _View::type_name_();
            wstring wid = to_wstring(id);
            return load_view(wid);
        }

        template<class _View>
        static _View& show_view(view_ptr& _p)
        {
            _p = get_view<_View>();
            _p->show();
            return _p->cast<_View>();
        }

        static view_ptr show_view(const wstring& _id)
        {
            view_ptr p = load_view(_id);
            if (p)
                p->show();
            return p;
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

        static cmdargs const& cmdargs()
        {
            return instance().args_;
        }

        static strings& filepaths()
        {
            return instance().paths_;
        }

    protected:
        virtual void on_init() { }

        virtual void on_fini() { }

    private:
        void load_cfgs(const wchar_t* _cmdline);

    };

}
