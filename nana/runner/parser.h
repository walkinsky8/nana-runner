// Created by walkinsky(lyh6188@hotmail.com), 2017/01/16
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/istr.h>
#include <nana/runner/optional.h>
#include <nana/runner/id.h>

#include <nana/runner/node.h>

namespace nana::runner
{
    class parser
    {
        node inner_;
        const node* outer_{};

    public:
        parser(istr _s);
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
        void operator >> (short& _v) const
        {
            readValue(_v);
        }
        void operator >> (int& _v) const
        {
            readValue(_v);
        }
        void operator >> (unsigned& _v) const
        {
            readValue(_v);
        }
        void operator >> (long& _v) const
        {
            readValue(_v);
        }
        void operator >> (int64& _v) const
        {
            readValue(_v);
        }
        void operator >> (float& _v) const
        {
            readValue(_v);
        }
        void operator >> (double& _v) const
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
        void operator >> (id& _v) const
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
        template<class T>
        void operator >> (std::shared_ptr<T>& _v) const
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

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const parser& _v)
    {
        return _v.dump(_os);
    }

    template<class T>
    inline void operator >> (const parser& _p, basic_point<T>& _v)
    {
        std::vector<T> values;
        _p >> values;
        if (values.size() > 0)
            _v.x = values[0];
        if (values.size() > 1)
            _v.y = values[1];
    }

    inline void operator >> (const parser& _p, size& _v)
    {
        std::vector<size::value_type> values;
        _p >> values;
        if (values.size() > 0)
            _v.width = values[0];
        if (values.size() > 1)
            _v.height = values[1];
    }

}
