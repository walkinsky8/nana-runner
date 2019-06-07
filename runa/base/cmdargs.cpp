/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/01/31
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/cmdargs.h>

void runa::cmdargs::init(const wchar_t* _cmdline)
{
    const wchar_t* p = _cmdline;
    while (*p)
    {
        if (*p == L'/' && *(p + 1) == L'*')
        {
            p += 2;
            while (*p && (*p != L'*' || *(p + 1) != L'/'))
                ++p;
            if (*p)
                ++++p;
            continue;
        }
        cmdline_ += *p;
        ++p;
    }
    string_split(cmdline_, args_);

    for (size_t i = 0; i < args_.size(); ++i)
    {
        auto const & s = args_[i];
        if (s[0] == '-')
        {
            wstring name(s);
            name.erase(0, 1);
            
            wstring value;
            if (i + 1 < args_.size())
            {
                if (args_[i+1][0] != '-')
                    value = args_[++i];
            }

            options_.add(name, value);
        }
        else
        {
            arguments_.push_back(s);
        }
    }
}

#endif

