// Created by walkinsky(lyh6188@hotmail.com), 2018/01/31
#pragma once

#include <nana/runner/base_config.h>

#include <nana/runner/list_multimap.h>

namespace nana::runner {

    class cmdargs
    {
        wstring cmdline_;
        std::vector<wstring> args_;

        typedef list_multimap<wstring, wstring> _Options;
        _Options options_;
        std::vector<wstring> arguments_;

    public:
        void init(const wchar_t* _cmdline);

        bool has_option(const wstring& _key) const
        {
            auto found = options_.find(_key);
            return found != nullptr;
        }
        
        wstring get_option(const wstring& _key) const
        {
            auto found = options_.find(_key);
            if (found)
                return *found;
            return{};
        }

        _Options::_Range options(const wstring& _key) const
        {
            return options_.equal_range(_key);
        }

        std::vector<wstring> const & arguments() const
        {
            return arguments_;
        }

    };

}
