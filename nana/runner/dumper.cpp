// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/dumper.h>

nana::runner::dumper& nana::runner::dumper::indent()
{
    if (compact_)
        return write(tag::space);

    write(tag::newline);
    for (int i = 0; i < level_; ++i)
        write(tag::indent);
    return *this;
}

nana::runner::dumper& nana::runner::dumper::writeName(string _name)
{
    write(_name);
    //if (!compact_)
    //    write(tag::space);
    write(tag::assign);
    //if (!compact_)
    //    write(tag::space);
    return *this;
}

nana::runner::dumper& nana::runner::dumper::enter(string _type)
{
    if (!_type.empty())
        write(tag::type).write(_type);
    write(tag::begin);
    ++level_;
    return *this;
}

nana::runner::dumper& nana::runner::dumper::leave()
{
    --level_;
    return indent().write(tag::end);
}

nana::runner::dumper& nana::runner::operator<<(dumper& _d, const nana::paint::font& _v)
{
    bool old = _d.compact(true);
    _d.enter({});
    _d.indent().write(_v.name());
    _d.indent().write(_v.size());
    if (_v.bold())
        _d.indent().write("bold");
    if (_v.italic())
        _d.indent().write("italic");
    if (_v.strikeout())
        _d.indent().write("strikeout");
    if (_v.underline())
        _d.indent().write("underline");
    _d.leave();
    _d.compact(old);
    return _d;
}
