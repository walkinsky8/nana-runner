/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/03/03
#pragma once

#include <runa/foundation/controller_base.h>

#include <runa/foundation/font/font_view_impl.h>

#include <runa/foundation/font/font_model.h>

namespace runa {

    class font_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(font_cntrl, controller_obj);

        view_ptr view_;

        using model_type = font_model;
        model_proxy<model_type> model_;

    public:
        font_cntrl();
        ~font_cntrl();

        void open(const model_type& _input, model_type::on_result _on_result);

        void close();

    };

}

