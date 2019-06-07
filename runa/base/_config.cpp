/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/_config.h>

#include <runa/base/base.h>

std::string runa::to_string(const wstring& _wstr)
{
    return nana::to_utf8(_wstr);
}

std::wstring runa::to_wstring(const string& _utf8str)
{
    return nana::to_wstring(_utf8str);
}

void runa::string_split(const string& _s, std::vector<string>& _ss)
{
    parser ps{ _s, true };
    ps >> _ss;
}

void runa::string_split(const wstring& _s, std::vector<wstring>& _ss)
{
    string u8s;
    u8s << _s;
    parser ps{ u8s, true };
    ps >> _ss;
}

runa::strings runa::strings_from(const string& _s, const string& _sep)
{
    strings ss;
    istr sep(_sep);
    istr p{ _s };
    istr beg = p;
    while (p)
    {
        if (!p.starts_with(sep))
        {
            ++p;
            continue;
        }
        ss.push_back(istr{ beg, p });
        p += (int)sep.size();
        beg = p;
    }
    if (p - beg > 0)
        ss.push_back(istr{ beg, p });
    return ss;
}

runa::strings runa::strings_sub(const strings& _ss, int _start, size_t _len)
{
    strings result;
    if (_start < 0)
        _start += (int)_ss.size();
    if (_start >= (int)_ss.size())
        _start = (int)_ss.size();
    if (_len > _ss.size() - _start)
        _len = _ss.size() - _start;
    for (; _len; ++_start, --_len)
        result.push_back(_ss[_start]);
    return result;
}

runa::string runa::strings_merge(const strings& _ss, const string& _sep)
{
    string s;
    for (size_t i = 0; i < _ss.size(); ++i)
    {
        if (i)
            s += _sep;
        s += _ss[i];
    }
    return s;
}

void runa::string_tolower(string& _s)
{
    std::transform(_s.begin(), _s.end(), _s.begin(), [](char ch) {
        if ('A' <= ch && ch <= 'Z')
            return static_cast<char>(ch - 'A' + 'a');
        return ch;
    });
}

void runa::string_toupper(string& _s)
{
    std::transform(_s.begin(), _s.end(), _s.begin(), [](char ch) {
        if ('a' <= ch && ch <= 'z')
            return static_cast<char>(ch - 'a' + 'A');
        return ch;
    });
}

bool runa::read_file(const wstring& _filename, string& _content)
{
    std::ifstream ifs{ to_string(_filename) };
    if (!ifs)
    {
        return false;
    }

    string line;
    while (ifs)
    {
        std::getline(ifs, line);
        if (line.size() > 2)
        {
            if (line[0] == '\xef' && line[1] == '\xbb' && line[2] == '\xbf')
                line.erase(0, 3);
        }
        if (line.size() > 0)
            if (line[0] == '\r')
                line.erase(0, 1);
        if (line.size() > 0)
            if (line[line.size() - 1] == '\r')
                line.erase(line.size() - 1, 1);
        if (!line.empty())
        {
            _content += line;
            _content += "\n";
        }
    }
    return true;
}

bool runa::write_file(const wstring& _filename, const string& _content)
{
    std::ofstream ofs{ to_string(_filename) };
    if (!ofs)
    {
        return false;
    }

    ofs.write("\xef\xbb\xbf", 3);
    istr p{ _content };
    while (p)
    {
        istr line = p.read_until(is_newline);
        p.read(is_newline);
        ofs.write(line.data(), line.size());
        ofs << "\n";
    }
    return true;
}

#endif

