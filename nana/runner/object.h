// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#pragma once

#include <nana/runner/base.h>

#define NAR_DEFINE_OBJECT(_class, _super) \
        private: \
            using super = _super; \
            using self = _class; \
        public: \
            static pcstr type_name_() { return #_class; } \
            static obj_ptr new_() { return std::make_shared<self>(); } \
        public: \
            string type_name() const override { return type_name_(); } \
            dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); } \
            void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); } \
        private:

namespace nana::runner {

    class object;
    using obj_ptr = ptr<object>;

    class object
    {
    public:
        virtual ~object() = default;

		template<class T>
		T& cast()
		{
			return dynamic_cast<T&>(*this);
		}

		template<class T>
		const T& cast() const
		{
			return dynamic_cast<const T&>(*this);
		}

        template<class _Stream>
        void traverse(_Stream& _s)
        {
        }

        virtual string type_name() const = 0;

        virtual dumper& dump(dumper& _d) const = 0;

        virtual void parse(const parser& _p) = 0;

    };

    inline dumper& operator<<(dumper& _d, const object& _v)
    {
        return _v.dump(_d);
    }

    inline void operator>>(const parser& _p, object& _v)
    {
        _v.parse(_p);
    }

    inline std::ostream& operator<<(std::ostream& _os, const object& _v)
    {
        dumper d{ true };
        d << _v;
        return _os << d;
    }

}

