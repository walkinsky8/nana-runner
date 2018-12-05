// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
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

