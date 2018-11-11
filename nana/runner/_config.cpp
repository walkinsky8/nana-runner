// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/_config.h>

#include <nana/runner/base.h>

std::ostream& std::operator<<(ostream& _os, const wstring& _v)
{
    _os << nana::runner::to_string(_v);
    return _os;
}

std::string& std::operator<<(std::string& _s, const std::wstring& _v)
{
    return _s << nana::to_utf8(_v);
}

std::string& std::operator<<(std::string& _s, const wchar_t* _v)
{
    return _s << std::wstring(_v);
}

void std::operator >> (const std::string& _s, std::wstring& _v)
{
    _v = nana::to_wstring(_s);
}

std::string nana::runner::to_string(const wstring& _wstr)
{
    return nana::to_utf8(_wstr);
}

std::wstring nana::runner::to_wstring(const string& _utf8str)
{
    return nana::to_wstring(_utf8str);
}

void nana::runner::string_split(const string& _s, std::vector<string>& _ss)
{
    parser ps{ _s, true };
    ps >> _ss;
}

void nana::runner::string_split(const wstring& _s, std::vector<wstring>& _ss)
{
    string u8s;
    u8s << _s;
    parser ps{ u8s, true };
    ps >> _ss;
}

nana::runner::strings nana::runner::strings_from(const string& _s, const string& _sep)
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

nana::runner::strings nana::runner::strings_sub(const strings& _ss, int _start, size_t _len)
{
    strings result;
    if (_start < 0)
        _start += (int)_ss.size();
    if (_start >= _ss.size())
        _start = (int)_ss.size();
    if (_len > _ss.size() - _start)
        _len = _ss.size() - _start;
    for (; _len; ++_start, --_len)
        result.push_back(_ss[_start]);
    return result;
}

nana::runner::string nana::runner::strings_merge(const strings& _ss, const string& _sep)
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

bool nana::runner::read_file(const wstring& _filename, string& _content)
{
    std::ifstream ifs{ _filename };
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

bool nana::runner::write_file(const wstring& _filename, const string& _content)
{
    std::ofstream ofs{ _filename };
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

