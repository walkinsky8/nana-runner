// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_all.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/panel_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/categorize_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/picture_cfg.h>
#include <nana/runner/group_cfg.h>

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
}

