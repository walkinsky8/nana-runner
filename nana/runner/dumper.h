// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/base_types.h>

namespace nana::runner
{
    template <class _Dumper, class _Type, bool _Dumpable = false>
    struct dump_out
    {
        _Dumper& operator()(_Dumper& _d, const _Type& _v)
        {
            return _d.write(_v);
        }
    };

    template <class _Dumper, class _Type>
    struct dump_out<_Dumper, _Type, true>
    {
        _Dumper& operator()(_Dumper& _d, const _Type& _v)
        {
            return codec(_d, const_cast<_Type&>(_v));
        }
    };

    class dumper
    {
        string oss_;
        bool compact_;
        int level_;
        bool hideEmpty_;

    public:
        dumper(bool _compact = false, int _level = 0, bool _hideEmpty = false)
            : compact_{ _compact }, level_{ _level }, hideEmpty_{ _hideEmpty }
        {}

        string const& str() const
        {
            return oss_;
        }

        bool compact() const
        {
            return compact_;
        }

        bool compact(bool _c)
        {
            bool old = compact_;
            compact_ = _c;
            return old;
        }

        template<class T>
        dumper& write(const T& _v)
        {
            oss_ << _v;
            return *this;
        }

        dumper& writeString(const istr& _v);

        dumper& operator<<(const string& _v)
        {
            return writeString(_v);
        }
        dumper& operator<<(const wstring& _v)
        {
            return writeString(to_string(_v));
        }
        dumper& operator<<(const char* _v)
        {
            return writeString(_v);
        }
        dumper& operator<<(const wchar_t* _v)
        {
            return writeString(to_string(_v));
        }

        template<class T>
        dumper& operator<<(const T& _v)
        {
            return dump_out<dumper, T, dumpable<T>::value>()(*this, _v);
        }

        template<class T>
        dumper& operator<<(const optional<T>& _v)
        {
            if (!_v.empty())
                *this << _v.value();
            return *this;
        }

        template<class T, T _Def>
        dumper& operator<<(const enum_<T, _Def>& _v)
        {
            return write(_v.str());
        }

        template<class T>
        dumper& operator<<(const ptr<T>& _v)
        {
            if (!_v)
                return write("null");
            else
                return (*this) << *_v;
        }

        template<class T>
        dumper& operator<<(const std::vector<T>& _v)
        {
            enter({});
            unnamed(_v);
            leave();
            return *this;
        }

        dumper& indent();

        dumper& writeName(string _name);

        dumper& enter(string _type);

        dumper& leave();

        template<class T>
        dumper& operator()(string _name, const T& _v)
        {
            if (!hideEmpty_ || !is_empty(_v))
                return indent().writeName(_name) << _v;
            return *this;
        }

        template<class T>
        dumper& unnamed(const std::vector<T>& _v)
        {
            for (const auto& i : _v)
            {
                indent() << i;
            }
            return *this;
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const dumper& _v)
    {
        return _os << _v.str();
    }

    template<class T>
    inline string dump(const T& _v, bool _compact=false, int _level=0, bool _hideEmpty=false)
    {
        dumper d{ _compact, _level, _hideEmpty };
        d << _v;
        return d.str();
    }

}
