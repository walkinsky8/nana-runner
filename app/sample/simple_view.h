/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/01/19
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/label_cfg.h>
#include <runa/widgets/textbox_cfg.h>
#include <runa/widgets/button_cfg.h>

namespace runa { namespace sample {

    class simple_view : public view_obj
    {
        NAR_DEFINE_VIEW(simple, view_obj);

        label& label_;

        textbox& textbox_;

        button& close_;

    public:
        simple_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , label_{ wnd<label>("label") }
            , textbox_{ wnd<textbox>("textbox") }
            , close_{ wnd<button>("close") }
        {
            close_.events().click([this] { close(); });
        }

    };

}}
