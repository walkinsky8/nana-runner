// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#include <nana/runner/id.h>

nana::runner::istr& nana::runner::istr::advance(int _offset)
{
    if (_offset > (int)size_)
        _offset = (int)size_;
    data_ += _offset;
    size_ -= _offset;
    return *this;
}

int nana::runner::istr::compare(istr _v) const
{
    size_t n = size();
    if (n > _v.size())
        n = _v.size();
    for (size_t i = 0; i < n; ++i)
    {
        if (me()[i] < _v[i])
            return -1;
        if (me()[i] > _v[i])
            return 1;
    }
    if (size() < _v.size())
        return -1;
    if (size() > _v.size())
        return 1;
    return 0;
}

