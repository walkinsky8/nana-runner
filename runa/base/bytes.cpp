/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/11/11
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/bytes.h>

bool runa::bytes::is_base64_char(const char _c)
{
    return between(_c, 'A', 'Z') || between(_c, 'a', 'z') || between(_c, '0', '9') || _c == '+' || _c == '/' || _c == '=';
}

char runa::bytes::peek_base64_char(istr & _s)
{
    while (_s && !is_base64_char(*_s))
        ++_s;
    return *_s++;
}

runa::byte runa::bytes::from_base64_char(const char _c)
{
    if (between(_c, 'A', 'Z'))
        return _c - 'A';
    if (between(_c, 'a', 'z'))
        return _c - 'a' + 26;
    if (between(_c, '0', '9'))
        return _c - '0' + 52;
    if (_c == '+')
        return 62;
    if (_c == '/')
        return 63;
    return 0;
}

char runa::bytes::to_base64_char(const byte _b)
{
    if (_b < 26)
        return _b + 'A';
    if (_b < 52)
        return _b - 26 + 'a';
    if (_b < 62)
        return _b - 52 + '0';
    if (_b == 62)
        return '+';
    if (_b == 63)
        return '/';
    return 0;
}

void runa::bytes::from_base64(istr _s)
{
    buf_.clear();
    while (_s)
    {
        char c1 = peek_base64_char(_s);
        char c2 = peek_base64_char(_s);
        char c3 = peek_base64_char(_s);
        char c4 = peek_base64_char(_s);
        if (!c1)
            break;
        byte b1 = from_base64_char(c1);
        byte b2 = from_base64_char(c2);
        byte b3 = from_base64_char(c3);
        byte b4 = from_base64_char(c4);
        buf_ += char((b1 << 2) | (b2 >> 4));
        if (c3 != '=')
            buf_ += char(((b2 & 0xf) << 4) | (b3 >> 2));
        if (c4 != '=')
            buf_ += char(((b3 & 0x3) << 6) | b4);
    }
}

std::string runa::bytes::to_base64() const
{
    string s;
    const size_t sz = size();
    if (!sz)
        return s;
    for (size_t i = 0; i < sz; i += 3)
    {
        byte b1 = 0, b2 = 0, b3 = 0;
        if (i < sz)
            b1 = data()[i];
        if (i + 1 < sz)
            b2 = data()[i + 1];
        if (i + 2 < sz)
            b3 = data()[i + 2];
        char c1 = to_base64_char(b1 >> 2);
        char c2 = to_base64_char(((b1 & 0x3) << 4) | (b2 >> 4));
        char c3 = to_base64_char(((b2 & 0xf) << 2) | (b3 >> 6));
        char c4 = to_base64_char(b3 & 0x3f);
        s += c1;
        s += c2;
        s += (i + 1 < sz) ? c3 : '=';
        s += (i + 2 < sz) ? c4 : '=';
    }
    return s;
}

#endif

