// Created by walkinsky(lyh6188@hotmail.com), 2018/11/15
#include "stdafx.h"

#include <nana/runner/sample/demo_app.h>

using namespace nana::runner::sample;

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
