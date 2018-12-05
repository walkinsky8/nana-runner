// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <runa/editor/editor_cntrl.h>

#include <runa/editor/logger_view_impl.h>
#include <runa/editor/editor_view_impl.h>
#include <runa/editor/editor_setup_view_impl.h>
#include <runa/foundation/color/color_view_impl.h>

#include <runa/foundation/app_base.h>

using namespace runa::editor;
using namespace runa;

editor_cntrl::editor_cntrl()
{
    add_view<logger_view_impl>();
    add_view<editor_view_impl>();
    add_view<editor_setup_view_impl>();
    add_view<color_view_impl>();
}

void editor_cntrl::open(callback _on_complete)
{
    auto& v_logger = app::show_view<logger_view_impl>(logger_);
    v_logger.init_log_handler();

    auto& v_editor = app::show_view<editor_view_impl>(editor_);
    v_editor.setup_.events().click([&] {
        auto& v_editor_setup = app::show_view<editor_setup_view_impl>(editor_setup_);
        v_editor_setup.set_target(&v_editor.filebuf_);
    });
}

void editor_cntrl::close()
{
    close_view(logger_);
    close_view(editor_);
    close_view(editor_setup_);
}

