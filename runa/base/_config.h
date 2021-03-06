/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2017/01/15
#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cassert>

#include <vector>
#include <queue>
#include <map>

#include <functional>
#include <ratio>
#include <chrono>

#include <nana/gui.hpp>
#include <nana/system/platform.hpp>
#include <nana/filesystem/filesystem.hpp>
#include <nana/filesystem/filesystem_ext.hpp>

#if defined(_MSC_VER)	//Microsoft Visual C++
#pragma warning(disable : 4100)
#endif

#define NAR_V(x) m_##x
#define NAR_F(x) x##_

#define NAR_FIELD_(t, x, v) \
        public: \
            t& NAR_F(x)() { return NAR_V(x); } \
            t const& NAR_F(x)() const { return NAR_V(x); } \
            void NAR_F(x)(t const& _v) { NAR_V(x) = _v; } \
        private: \
            t NAR_V(x){ v }

#define NAR_FIELD(t, x) NAR_FIELD_(t, x, )

#define NAR_CODEC(s, x) s(#x, NAR_V(x))
#define NAR_CODEC_UNNAMED(s, x) s.unnamed(NAR_V(x))
#define NAR_CODEC_SUPER(s) super::traverse(s)

namespace std {

    template<class _Ch, class T>
    inline std::basic_string<_Ch>& operator<<(std::basic_string<_Ch>& _s, const T& _v)
    {
        std::basic_ostringstream<_Ch> oss;
        oss << _v;
        return _s += oss.str();
    }
    template<class _Ch>
    inline std::basic_string<_Ch>& operator<<(std::basic_string<_Ch>& _s, const std::basic_string<_Ch>& _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, char _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, wchar_t _v)
    {
        wchar_t ws[] = { _v, 0 };
        return _s += nana::to_utf8(ws);
    }
    inline std::string& operator<<(std::string& _s, const char* _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, const wchar_t* _v)
    {
        return _s += nana::to_utf8(_v);
    }
    inline std::string& operator<<(std::string& _s, const std::wstring& _v)
    {
        return _s += nana::to_utf8(_v);
    }
    inline std::wstring& operator<<(std::wstring& _s, char _v)
    {
        return _s += _v;
    }
    inline std::wstring& operator<<(std::wstring& _s, wchar_t _v)
    {
        return _s += _v;
    }
    inline std::wstring& operator<<(std::wstring& _s, const char* _v)
    {
        return _s += nana::to_wstring(_v);
    }
    inline std::wstring& operator<<(std::wstring& _s, const wchar_t* _v)
    {
        return _s += _v;
    }
    inline std::wstring& operator<<(std::wstring& _s, const std::string& _v)
    {
        return _s += nana::to_wstring(_v);
    }

    template<class _Ch, class T>
    inline void operator>>(const std::basic_string<_Ch>& _s, T& _v)
    {
        if (!_s.empty())
        {
            std::basic_istringstream<_Ch> iss{ _s };
            iss >> _v;
        }
    }
    template<class _Ch>
    inline void operator>>(const std::basic_string<_Ch>& _s, std::basic_string<_Ch>& _v)
    {
        if (!_s.empty())
            _v = _s;
    }
    inline void operator>>(const std::string& _s, std::wstring& _v)
    {
        if (!_s.empty())
            _v = nana::to_wstring(_s);
    }
    inline void operator>>(const std::wstring& _s, std::string& _v)
    {
        if (!_s.empty())
            _v = nana::to_utf8(_s);
    }

    inline ostream& operator<<(ostream& _os, const wstring& _v)
    {
        return _os << nana::to_utf8(_v);
    }

    inline ostream& operator<<(ostream& _os, const exception& _v)
    {
        return _os << _v.what();
    }

}

namespace runa {

    namespace fs = std::/*experimental::*/filesystem;
    namespace fs_ext = nana::filesystem_ext;

    namespace tag
    {
        const char key = '@';
        const char string = '\'';
        const char string2 = '"';
        const char begin = '{';
        const char end = '}';
        const char assign = '=';

        const char escape = '^';
        const char comment = '*';

        const char space = ' ';
        const char tab = '\t';
        const char cr = '\r';
        const char nl = '\n';

        const std::string s_newline{ "\n" };
        const std::string s_indent{ "    " };
        const std::string s_raw{ "'''" };
        const std::string s_raw2{ "\"\"\"" };
    }

    using nana::npos;

    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using byte = unsigned char;
    using uchar = unsigned char;
    using ushort = unsigned short;
    using uint = unsigned int;
    using ulong = unsigned long;
    using longlong = long long;
    using ulonglong = unsigned long long;

    using string = std::string;
    using wstring = std::wstring;

    using pcstr = const char*;
    using pcwstr = const wchar_t*;

    using strings = std::vector<string>;

	template<class T> using ptr = std::shared_ptr<T>;

    template<class T> using is_simple_type = std::is_arithmetic<T>;

	/*
	 * character functions
	 */

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

    inline bool is_quote_char(const char c) { return c == tag::string || c == tag::string2; }

    inline char to_upper(const char c) { return is_lower(c) ? (c - 'a' + 'A') : c; }
    inline char to_lower(const char c) { return is_upper(c) ? (c - 'A' + 'a') : c; }

	/*
	 * utility functions
	 */

    template<class T>
    inline bool is_empty(const T& _v) { return false; }
    inline bool is_empty(const string& _v) { return _v.empty(); }
    inline bool is_empty(const wstring& _v) { return _v.empty(); }
    template<class T>
    inline bool is_empty(const std::vector<T>& _v) { return _v.empty(); }

    template<class T>
    inline const T& min_(const T& _v1, const T& _v2)
    {
        return _v1 < _v2 ? _v1 : _v2;
    }

    template<class T>
    inline const T& min_(const T& _v1, const T& _v2, const T& _v3)
    {
        return min_(_v1, min_(_v2, _v3));
    }

    template<class T>
    inline const T& max_(const T& _v1, const T& _v2)
    {
        return _v1 > _v2 ? _v1 : _v2;
    }

    template<class T>
    inline const T& max_(const T& _v1, const T& _v2, const T& _v3)
    {
        return max_(_v1, max_(_v2, _v3));
    }

    template<class T>
    T ensure_between(T val, T low, T high)
    {
        if (val < low)
            val = low;
        if (val > high)
            val = high;
        return val;
    }

    /*
	 * string functions
	 */

    using std::to_string;

    string to_string(const wstring& _wstr);
    wstring to_wstring(const string& _utf8str);

    void string_split(const string& _s, std::vector<string>& _ss);
    void string_split(const wstring& _s, std::vector<wstring>& _ss);

    strings strings_from(const string& _s, const string& _sep);
    strings strings_sub(const strings& _ss, int _start, size_t _len = npos);
    string strings_merge(const strings& _ss, const string& _sep);

    void string_toupper(string& s);
    void string_tolower(string& s);
    inline string to_upper(const string& s) { string tmp{ s }; string_toupper(tmp); return tmp; }
    inline string to_lower(const string& s) { string tmp{ s }; string_tolower(tmp); return tmp; }

    template<class T>
    inline std::string to_str(const T& _v)
    {
        std::ostringstream oss;
        oss << _v;
        return oss.str();
    }
	/*
	 * file functions
	 */

	bool read_file(const wstring& _filename, string& _content);
	bool write_file(const wstring& _filename, const string& _content);

	/*
	 * codec template function
	 */

	template<class _Stream, class T>
    inline _Stream& codec(_Stream& _s, T& _v)
    {
        _s.enter(_v.type_name());
        _v.traverse(_s);
        _s.leave();
        return _s;
    }

}

