// nana_runner_all_in_one.cpp : include all source files
//
#include "stdafx.h"

#ifdef __NANA_RUNNER_LIB_ALL_IN_ONE
#undef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/_config.cpp>

#include <nana/runner/base.cpp>
#include <nana/runner/object.cpp>
#include <nana/runner/dumper.cpp>
#include <nana/runner/node.cpp>
#include <nana/runner/parser.cpp>
#include <nana/runner/log.cpp>
#include <nana/runner/mt_thread.cpp>
#include <nana/runner/bytes.cpp>
#include <nana/runner/datetime.cpp>
#include <nana/runner/id.cpp>
#include <nana/runner/istr.cpp>
#include <nana/runner/cmdargs.cpp>
#include <nana/runner/util.cpp>

#include <nana/runner/app_base.cpp>
#include <nana/runner/controller_base.cpp>
#include <nana/runner/model_base.cpp>
#include <nana/runner/font_model.cpp>
#include <nana/runner/view_base.cpp>
#include <nana/runner/view_factory.cpp>
#include <nana/runner/widget_base.cpp>
#include <nana/runner/widget_cfg.cpp>
#include <nana/runner/widget_factory.cpp>

#include <nana/runner/button_cfg.cpp>
#include <nana/runner/categorize_cfg.cpp>
#include <nana/runner/checkbox_cfg.cpp>
#include <nana/runner/combox_cfg.cpp>
#include <nana/runner/form_cfg.cpp>
#include <nana/runner/group_cfg.cpp>
#include <nana/runner/label_cfg.cpp>
#include <nana/runner/listbox_cfg.cpp>
#include <nana/runner/menu_cfg.cpp>
#include <nana/runner/menubar_cfg.cpp>
#include <nana/runner/panel_cfg.cpp>
#include <nana/runner/panel_lite_cfg.cpp>
#include <nana/runner/picture_cfg.cpp>
#include <nana/runner/progress_cfg.cpp>
#include <nana/runner/scroll_cfg.cpp>
#include <nana/runner/slider_cfg.cpp>
#include <nana/runner/spinbox_cfg.cpp>
#include <nana/runner/tab_cfg.cpp>
#include <nana/runner/tabbar_cfg.cpp>
#include <nana/runner/textbox_cfg.cpp>
#include <nana/runner/toolbar_cfg.cpp>
#include <nana/runner/treebox_cfg.cpp>
#include <nana/runner/widget_all.cpp>

#endif

