/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#include "stdafx.h"

#include <runa/editor/editor_app.h>

using namespace runa::editor;

editor_app::editor_app()
{
}

void editor_app::on_init()
{
    login_.open([&] {
        editor_.open(nullptr);
    });
}

void editor_app::on_fini()
{
    login_.close();
    editor_.close();
}

