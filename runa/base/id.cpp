/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/11/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/id.h>

runa::id& runa::id::format()
{
    if (istr{ path_ }.read(is_identifier_body).size() == path_.size())
        return *this;
    for (auto i = path_.begin(); i != path_.end(); ++i)
    {
        if (!is_identifier_body(*i))
            *i = separator;
    }
    int seps = 0;
    for (size_t i = 0; i < path_.size(); ++i)
    {
        if (path_[i] == separator)
            ++seps;
        else
        {
            if (seps > 1)
            {
                path_.erase(i - seps, seps - 1);
                i -= seps - 1;
            }
            seps = 0;
        }
    }
    return *this;
}

runa::id& runa::id::operator/(const id& _child)
{
    if (!path_.empty())
        path_ << separator;
    path_ << _child;
    return *this;
}

#endif

