// Created by walkinsky(lyh6188@hotmail.com), 2018/02/09
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/combox_cfg.h>
#include <nana/runner/button_cfg.h>
#include <nana/runner/textbox_cfg.h>

namespace nana::runner::sample {

    class editor_view : public view_obj
    {
        NAR_DEFINE_VIEW(editor, view_obj);

    public:
        form& form_;

        combox& folder_;
        button& choose_dir_;
        combox& file_;
        button& open_file_;

        textbox& filebuf_;

        button& load_;
        button& save_;
        button& run_;
        button& setup_;
        button& quit_;

    public:
        self(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
            , form_{ wnd<form>() }
            , folder_{ wnd<combox>("folder.value") }
            , choose_dir_{ wnd<button>("folder.choose_dir") }
            , file_{ wnd<combox>("file.value") }
            , open_file_{ wnd<button>("file.open_file") }
            , filebuf_{ wnd<textbox>("filebuf") }
            , load_{ wnd<button>("cmd.load") }
            , save_{ wnd<button>("cmd.save") }
            , run_{ wnd<button>("cmd.run") }
            , setup_{ wnd<button>("cmd.setup") }
            , quit_{ wnd<button>("cmd.close") }
        {
        }

    };

}

