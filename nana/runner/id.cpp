// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include <nana/runner/id.h>

nana::runner::id& nana::runner::id::format()
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

nana::runner::id& nana::runner::id::operator/(const id& _child)
{
    if (!path_.empty())
        path_ << separator;
    path_ << _child;
    return *this;
}
