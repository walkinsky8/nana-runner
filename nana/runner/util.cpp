// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/util.h>

void nana::runner::write_console(const string& _msg)
{
    OutputDebugStringW(to_wstring(_msg).c_str());
}

nana::runner::pcstr nana::runner::find_classfunc(pcstr _func)
{
    pcstr beg = _func;
    pcstr end = beg + std::strlen(beg);
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

