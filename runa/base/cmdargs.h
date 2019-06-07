/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/31
#pragma once

#include <runa/base/_config.h>

#include <runa/base/list_multimap.h>

namespace runa {

    class cmdargs
    {
    public:
        typedef list_multimap<wstring, wstring> _Options;
        typedef _Options::_Range _Range;

    private:
        wstring cmdline_;
        std::vector<wstring> args_;

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

        _Range options(const wstring& _key) const
        {
            return options_.equal_range(_key);
        }

        std::vector<wstring> const & arguments() const
        {
            return arguments_;
        }

    };

}
