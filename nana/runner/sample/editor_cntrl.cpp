// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_cntrl.h>

#include <nana/runner/sample/logger_view_impl.h>
#include <nana/runner/sample/editor_view_impl.h>
#include <nana/runner/sample/editor_setup_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;
using namespace nana::runner;

editor_cntrl::editor_cntrl()
{
    add_view<logger_view_impl>();
    add_view<editor_view_impl>();
    add_view<editor_setup_view_impl>();
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

