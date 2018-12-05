// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <runa/base/_config.h>

#include <runa/base/base_types.h>

#include <runa/base/node.h>

namespace runa
{
    class parser
    {
        node inner_;
        const node* outer_{};

    public:
        parser(istr _s, bool _is_list=false);
        parser(const node* _outer);

        const node& unit() const;

        const string& type() const
        {
            return unit().type();
        }

        const string& value() const
        {
            return unit().value();
        }

        bool valueIsEmpty() const
        {
            return unit().valueIsEmpty();
        }

        template<class T>
        void readValue(T& _v) const
        {
            value() >> _v;
        }

        void operator >> (bool& _v) const
        {
            readValue(_v);
        }
        void operator >> (char& _v) const
        {
            readValue(_v);
        }
        void operator >> (uchar& _v) const
        {
            readValue(_v);
        }
        void operator >> (short& _v) const
        {
            readValue(_v);
        }
        void operator >> (ushort& _v) const
        {
            readValue(_v);
        }
        void operator >> (int& _v) const
        {
            readValue(_v);
        }
        void operator >> (uint& _v) const
        {
            readValue(_v);
        }
        void operator >> (long& _v) const
        {
            readValue(_v);
        }
        void operator >> (ulong& _v) const
        {
            readValue(_v);
        }
        void operator >> (int64& _v) const
        {
            readValue(_v);
        }
        void operator >> (uint64& _v) const
        {
            readValue(_v);
        }
        //void operator >> (size_t& _v) const
        //{
        //    readValue(_v);
        //}
        void operator >> (float& _v) const
        {
            readValue(_v);
        }
        void operator >> (double& _v) const
        {
            readValue(_v);
        }
        void operator >> (long double& _v) const
        {
            readValue(_v);
        }
        void operator>>(string& _v) const
        {
            readValue(_v);
        }
        void operator>>(wstring& _v) const
        {
            readValue(_v);
        }
        void operator>>(bytes& _v) const
        {
            readValue(_v);
        }
        void operator>>(datetime& _v) const
        {
            readValue(_v);
        }
        void operator >> (id& _v) const
        {
            readValue(_v);
        }
        template<class T>
        void operator >> (number<T>& _v) const
        {
            readValue(_v);
        }
        template<class T>
        void operator >> (optional<T>& _v) const
        {
            if (!valueIsEmpty())
            {
                T value;
                *this >> value;
                _v.set_value(value);
            }
        }
        template<class T, T _Def>
        void operator>>(enum_<T, _Def>& _v) const
        {
            if (!valueIsEmpty())
            {
                _v = enum_<T, _Def>(value());
            }
        }
        template<class T>
        void operator >> (ptr<T>& _v) const
        {
            if (!valueIsEmpty())
            {
                _v = std::make_shared<T>();
                *this >> *value;
            }
        }
        template<class T>
        void operator>>(std::vector<T>& _v) const
        {
            if (unit().simple())
            {
                T value;
                *this >> value;
                _v.push_back(value);
            }
            else
            for (auto& n : unit().children().list())
            {
                parser child(&n);
                T value;
                child >> value;
                _v.push_back(value);
            }
        }
        template<class T>
        void operator>>(T& _v) const
        {
            codec(const_cast<parser&>(*this), _v);
        }

        void enter(string& _type) const
        {
            _type = unit().type();
        }

        void leave() const
        {
        }

        template<class T>
        void operator()(string _name, T& _v) const
        {
            const node* child_node = unit().child(_name);
            if (child_node)
            {
                parser child{ child_node };
                child >> _v;
            }
        }
        template<class T>
        void unnamed(std::vector<T>& _v) const
        {
            auto range = unit().child_equal({});
            for (auto i=range.first; i!=range.second; ++i)
            {
                parser child(&(*i).second);
                T value;
                child >> value;
                _v.push_back(value);
            }
        }

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const parser& _v)
    {
        return _v.dump(_os);
    }

}
