// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>
#include <nana/runner/istr.h>

namespace nana::runner {

    class dumper
    {
        std::ostringstream oss_;

    public:
        dumper() = default;

        std::string str() const
        {
            return oss_.str();
        }

        dumper& writeString(const istr& _v)
        {
            oss_ << "'" << _v << "'";
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
            return write(_v);
        }

        template<class T>
        dumper& operator<<(const std::vector<T>& _v)
        {
            enter({});
            for (const auto& i : _v)
            {
                write(" ");
                *this << i;
            }
            leave();
            return *this;
        }

        dumper& enter(string _type)
        {
            if (!_type.empty())
                write("@").write(_type);
            return write("{");
        }

        dumper& leave()
        {
            return write(" }");
        }

        template<class T>
        dumper& operator()(string _name, const T& _v)
        {
            return write(" ").write(_name).write("=") << _v;
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const dumper& _v)
    {
        return _os << _v.str();
    }

    template<class T>
    string dump(const T& _v)
    {
        dumper d;
        return codec(d, const_cast<T&>(_v)).str();
    }

}
