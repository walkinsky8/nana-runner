// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
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

runa::dumper& runa::dumper::enter(string _type)
{
    if (!_type.empty())
        write(tag::key).write(_type);
    write(tag::begin);
    ++level_;
    return *this;
}

runa::dumper& runa::dumper::leave()
{
    --level_;
    return indent().write(tag::end);
}

#endif

