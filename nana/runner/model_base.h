// Created by walkinsky(lyh6188@hotmail.com), 2018/01/21
#pragma once

#include <nana/runner/base.h>

#define NAR_DEFINE_MODEL(_class, _super) \
        private: \
            using super = _super; \
            using self = _class; \
        public: \
            static pcstr type_name_() { return #_class; } \
            static model_ptr new_() { return std::make_shared<self>(); } \
        public: \
            string type_name() const override { return type_name_(); } \
            model_ptr new_obj() const override { return new_(); } \
            dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); } \
            void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); } \
        private:

namespace nana::runner {

    class model_obj;
    using model_ptr = ptr<model_obj>;

    class model_obj : public object
    {
    public:
        virtual string type_name() const = 0;

        virtual model_ptr new_obj() const = 0;

        virtual dumper& dump(dumper& _d) const = 0;

        virtual void parse(const parser& _p) = 0;

        template<class _Stream>
        void traverse(_Stream& _s)
        {
        }

    };

}
