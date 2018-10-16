// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_all.h>

void nana::runner::init_widgets()
{
    add_widget<form_cfg>();
    add_widget<panel_cfg>();
    add_widget<label_cfg>();
    add_widget<textbox_cfg>();
    add_widget<button_cfg>();
    add_widget<checkbox_cfg>();
    add_widget<categorize_cfg>();
    add_widget<slider_cfg>();
    add_widget<picture_cfg>();
    add_widget<group_cfg>();
    add_widget<option_cfg>();
    add_widget<combox_cfg>();
    add_widget<date_chooser_cfg>();
    add_widget<float_listbox_cfg>();
    add_widget<listbox_cfg>();
    add_widget<unknown_cfg>();
}

