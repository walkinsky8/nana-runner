// Created by walkinsky(lyh6188@hotmail.com), 2017/11/07
#pragma once

#include <runa/base/_config.h>

#define NAR_ENUM_ADD(e, d, i)     runa::enum_<e, e::d>::add(e::i, #i)
#define NAR_ENUM_ADD_(e, p, d, i) runa::enum_<e, e::p##d>::add(e::p##i, #i)

namespace runa {

    template<typename E, E _Default>
    class enum_
    {
        E value_;

    public:
        enum_()
            : value_{ _Default }
        {}
        enum_(E _value)
            : value_{ _value }
        {}
        enum_(string const& _s)
            : value_{ str2value(_s) }
        {}

        E& value()
        {
            return value_;
        }

        E value() const
        {
            return value_;
        }

        string str() const
        {
            return value2str(value_);
        }

        static void add(E v, string const& s)
        {
            v2s()[v] = s;
            s2v()[s] = v;
        }

        static string* find_name(unsigned _value)
        {
            const auto i = v2s().find((E)(int)_value);
            if (i != v2s().end())
                return &(*i).second;
            return nullptr;
        }

        static E* find_value(const string& s)
        {
            const auto i = s2v().find(s);
            if (i == s2v().end())
                return nullptr;
            return &(*i).second;
        }

        static E str2value(string const& s)
        {
            const auto i = s2v().find(s);
            if (i == s2v().end())
                return _Default;
            return (*i).second;
        }

        static string value2str(E v)
        {
            const auto i = v2s().find(v);
            if (i == v2s().end())
                return{};
            return (*i).second;
        }

        static std::map<E, string>& v2s()
        {
            static std::map<E, string> v2s_;
            return v2s_;
        }

        static std::map<string, E>& s2v()
        {
            static std::map<string, E> s2v_;
            return s2v_;
        }

    };
    template<typename E, E _Default>
    inline std::ostream& operator<<(std::ostream& _os, const enum_<E, _Default>& _v)
    {
        return _os << (int)_v.value();
    }
    template<typename E, E _Default>
    inline std::string& operator<<(std::string& _os, const enum_<E, _Default>& _v)
    {
        return _os << _v.str();
    }

    template<typename E, E _Default>
    void operator<<(strings& _names, const enum_<E, _Default>& _v)
    {
        for (auto& i : _v.v2s())
            _names.push_back(i.second);
    }

    template<typename E, E _Default>
    void operator<<(std::vector<int>& _values, const enum_<E, _Default>& _v)
    {
        for (auto& i : _v.v2s())
            _values.push_back(i.first);
    }

}
