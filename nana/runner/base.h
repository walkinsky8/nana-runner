// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <functional>

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
    inline std::string& operator<<(std::string& _s, char _v)
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

    using string = std::string;
    using wstring = std::wstring;

    using pcstr = const char*;
    using pcwstr = const wchar_t*;

    using strings = std::vector<string>;

    template<class T> struct dumpable { static constexpr bool value = false; };

    template<class T> using is_simple_type = std::is_arithmetic<T>;

    inline bool is_space(const char c) { return c == ' ' || c == '\t'; }
    inline bool is_newline(const char c) { return c == '\r' || c == '\n'; }
    inline bool is_blank(const char c) { return is_space(c) || is_newline(c); }

    inline bool between(const char c, const char beg, const char end) { return c >= beg && c <= end; }

    inline bool is_digit(const char c) { return between(c, '0', '9'); }
    inline bool is_upper(const char c) { return between(c, 'A', 'Z'); }
    inline bool is_lower(const char c) { return between(c, 'a', 'z'); }
    inline bool is_letter(const char c) { return is_upper(c) || is_lower(c); }
    inline bool is_identifier_start(const char c) { return is_letter(c) || c == '_'; }
    inline bool is_identifier_body(const char c) { return is_identifier_start(c) || is_digit(c); }

    inline bool is_hex_upper(const char c) { return between(c, 'A', 'F'); }
    inline bool is_hex_lower(const char c) { return between(c, 'a', 'f'); }
    inline bool is_hex_letter(const char c) { return is_hex_upper(c) || is_hex_lower(c); }
    inline bool is_hex16_char(const char c) { return is_hex_letter(c) || is_digit(c); }

    inline bool is_base64_char(const char c) { return is_letter(c) || is_digit(c) || c=='+' || c=='/' || c=='='; }

    template<class _Stream, class T>
    inline _Stream& codec(_Stream& _s, T& _v)
    {
        _s.enter(_v.type_name());
        _v.traverse(_s);
        _s.leave();
        return _s;
    }

    string to_string(const wstring& _wstr);
    wstring to_wstring(const string& _utf8str);

}

