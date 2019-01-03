// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/widgets/widget_all.h>

void runa::init_widgets()
{
    add_widget<form_cfg>();
    add_widget<panel_cfg>();
    add_widget<panel_lite_cfg>();
    add_widget<label_cfg>();
    add_widget<textbox_cfg>();
    add_widget<button_cfg>();
    add_widget<checkbox_cfg>();
    add_widget<categorize_cfg>();
    add_widget<picture_cfg>();
    add_widget<group_cfg>();
    add_widget<combox_cfg>();
    add_widget<date_chooser_cfg>();
    add_widget<float_listbox_cfg>();
    add_widget<listbox_cfg>();
    add_widget<menubar_cfg>();
    add_widget<menu_cfg>();
    add_widget<slider_cfg>();
    add_widget<progress_cfg>();
    add_widget<hscroll_cfg>();
    add_widget<vscroll_cfg>();
    add_widget<spinbox_cfg>();
    add_widget<tabbar_cfg>();
    add_widget<tabbar_lite_cfg>();
    add_widget<tabpage_cfg>();
    add_widget<tab_cfg>();
    add_widget<toolbar_cfg>();
    add_widget<treebox_cfg>();

    add_widget<color_chooser_cfg>();

    add_widget<option_cfg>();
    add_widget<unknown_cfg>();
}

#endif

