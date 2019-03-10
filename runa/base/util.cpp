/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/04
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/util.h>

void runa::write_console(const string& _msg)
{
    OutputDebugStringW(to_wstring(_msg).c_str());
}

runa::pcstr runa::find_classfunc(pcstr _func)
{
    pcstr beg = _func;
    pcstr end = beg + strlen(beg);
    pcstr p = end;
    int num = 2;
    while (num-- > 0)
    {
        if (p > beg)
            --p;
        while (p > beg && (*p != ':' || *(p - 1) != ':'))
        {
            --p;
        }
    }
    if (*p == ':')
        ++p;
    return p;
}

#endif

