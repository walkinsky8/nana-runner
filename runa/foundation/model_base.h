/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/01/21
#pragma once

#include <runa/base/object.h>

#define NAR_DEFINE_MODEL(_class, _super) \
        private: \
            using super = _super; \
            using self = _class##_model; \
        public: \
            static pcstr type_name_() { return #_class; } \
            static model_ptr new_() { return std::make_shared<self>(); } \
        public: \
            string type_name() const override { return type_name_(); } \
            dumper& dump(dumper& _d) const override { return codec(_d, const_cast<self&>(*this)); } \
            void parse(const parser& _p) override { codec(const_cast<parser&>(_p), *this); } \
        private:

namespace runa {

    class model_obj;
    using model_ptr = ptr<model_obj>;

    class model_obj : public object
    {
    };

    template<class _Model>
    struct model_proxy_base
    {
        using on_result = std::function<void(const _Model&)>;
    };

    template<class _Model>
    struct model_proxy : public model_proxy_base<_Model>
    {
        using super = model_proxy_base<_Model>;

        _Model data_;

        using super::on_result;
        on_result on_result_;

    public:
        model_proxy() = default;
        model_proxy(const _Model& _data, on_result _on_result)
            : data_{ _data }, on_result_{ _on_result }
        {
        }

        void operator()() const
        {
            if (on_result_)
                on_result_(data_);
        }

    };

}
