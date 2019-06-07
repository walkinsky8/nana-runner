/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/15
#include "stdafx.h"

#include "demo_app.h"

using namespace runa::sample;

demo_app::demo_app()
{
}

void demo_app::on_init()
{
    demo_.open(nullptr);
}

void demo_app::on_fini()
{
    demo_.close();
}

