/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/dumper.h>

runa::dumper& runa::dumper::writeString(const istr& _v)
{
    bool isNull = _v == istr("null");
    if (!isNull)
        oss_ << tag::string;
    oss_ << _v;
    if (!isNull)
        oss_ << tag::string;
    return *this;
}

runa::dumper& runa::dumper::indent()
{
    if (compact_)
        return write(tag::space);

    write(tag::s_newline);
    for (int i = 0; i < level_; ++i)
        write(tag::s_indent);
    return *this;
}

runa::dumper& runa::dumper::writeName(string _name)
{
    write(_name);
    //if (!compact_)
    //    write(tag::space);
    write(tag::assign);
    //if (!compact_)
    //    write(tag::space);
    return *this;
}

runa::dumper& runa::dumper::writeBegin()
{
    return write(tag::begin);
}

runa::dumper& runa::dumper::writeEnd()
{
    return write(tag::end);
}

runa::dumper& runa::dumper::enter(string _type)
{
    if (!_type.empty())
        write(tag::key).write(_type);
    writeBegin();
    ++level_;
    return *this;
}

runa::dumper& runa::dumper::leave()
{
    --level_;
    return indent().writeEnd();
}

#endif

