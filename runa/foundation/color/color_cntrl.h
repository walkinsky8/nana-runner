/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/12/04
#pragma once

#include <runa/foundation/controller_base.h>

#include <runa/foundation/color/color_view_impl.h>

#include <runa/foundation/color/color_model.h>

namespace runa {

    class color_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(color_cntrl, controller_obj);

        view_ptr view_;

        using model_type = color_model;
        model_proxy<model_type> model_;

    public:
        color_cntrl();
        ~color_cntrl();

        void open(const model_type& _input, model_type::on_result _on_result);

        void close();

    };

}

