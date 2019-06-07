/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/11/1
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/node.h>

#include <runa/base/dumper.h>

void runa::node::clear()
{
    name_.clear();
    type_.clear();
    value_.clear();
    children_.clear();
}

void runa::node::traverse(dumper& _d)
{
    for (auto& i : children_.list())
    {
        if (i.simple())
            _d(i.name(), i.value());
        else
            _d(i.name(), i.children().list());
    }
}

#endif

