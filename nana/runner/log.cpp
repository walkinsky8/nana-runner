// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/log.h>

nana::runner::out::~out()
{
    OutputDebugStringW(nana::to_wstring(oss_.str()).c_str());
}

nana::runner::log::log()
{
    oss_ << "--- ";
}

nana::runner::log::~log()
{
    oss_ << std::endl;
}

