// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

namespace std {

    template<class T>
    inline std::string& operator<<(std::string& _s, const T& _v)
    {
        std::ostringstream oss;
        oss << _v;
        return _s << oss.str();
    }
    inline std::string& operator<<(std::string& _s, const std::string& _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, const char* _v)
    {
        return _s += _v;
    }
    std::string& operator<<(std::string& _s, const std::wstring& _v);
    std::string& operator<<(std::string& _s, const wchar_t* _v);

}

namespace nana::runner {

    using std::string;
    using std::wstring;

    using pcstr = const char*;
    using pcwstr = const wchar_t*;

    template<class T> struct dumpable { enum { value = false }; };

    template<class T> using is_simple_type = std::is_arithmetic<T>;

    string to_string(const wstring& _wstr);

    template<class _Stream, class T>
    inline _Stream& codec(_Stream& _s, T& _v)
    {
        _s.enter(_v.type_name());
        _v.traverse(_s);
        _s.leave();
        return _s;
    }
}

