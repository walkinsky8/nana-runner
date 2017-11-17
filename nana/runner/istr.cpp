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
