// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>

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
        _content += line;
        _content += "\n";
    }
    return true;
}

void nana::runner::initialize()
{
    enum_<nana::colors, nana::colors::black>::add(nana::colors::black, "black");
    enum_<nana::colors, nana::colors::black>::add(nana::colors::white, "white");
    enum_<nana::colors, nana::colors::black>::add(nana::colors::red, "red");
    enum_<nana::colors, nana::colors::black>::add(nana::colors::green, "green");
    enum_<nana::colors, nana::colors::black>::add(nana::colors::blue, "blue");
}
