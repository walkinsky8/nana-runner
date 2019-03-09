/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/02/12
#pragma once

#include <runa/foundation/controller_base.h>

namespace runa::editor {

    class editor_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(editor_cntrl, controller_obj);

		view_ptr logger_;
        view_ptr editor_;
		view_ptr editor_setup_;

    public:
        editor_cntrl();

        void open(callback _on_complete, bool _nologwin);

        void close();

    };

}

