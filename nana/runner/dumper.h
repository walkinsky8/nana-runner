// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/istr.h>

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

        dumper& writeString(const istr& _v)
        {
            oss_ << tag::string << _v << tag::string;
            return *this;
        }

        template<class T>
        dumper& write(const T& _v)
        {
            oss_ << _v;
            return *this;
        }

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
        dumper& operator<<(const std::vector<T>& _v)
        {
            enter({});
            for (const auto& i : _v)
            {
                indent() << i;
            }
            leave();
            return *this;
        }

        dumper& indent()
        {
            if (compact_)
                return write(tag::space);

            write(tag::newline);
            for (int i = 0; i < level_; ++i)
                write(tag::indent);
            return *this;
        }

        dumper& writeName(string _name)
        {
            write(_name);
            //if (!compact_)
            //    write(tag::space);
            write(tag::assign);
            //if (!compact_)
            //    write(tag::space);
            return *this;
        }

        dumper& enter(string _type)
        {
            if (!_type.empty())
                write(tag::type).write(_type);
            write(tag::begin);
            ++level_;
            return *this;
        }

        dumper& leave()
        {
            --level_;
            return indent().write(tag::end);
        }

        template<class T>
        dumper& operator()(string _name, const T& _v)
        {
            if (!hideEmpty_ || !is_empty(_v))
                return indent().writeName(_name) << _v;
            return *this;
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const dumper& _v)
    {
        return _os << _v.str();
    }

    template<class T>
    string dump(const T& _v, bool _compact=false, int _level=0, bool _hideEmpty=false)
    {
        dumper d{ _compact, _level, _hideEmpty };
        return codec(d, const_cast<T&>(_v)).str();
    }

}
