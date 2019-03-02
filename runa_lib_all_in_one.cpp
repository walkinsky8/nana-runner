/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// nana_runner_all_in_one.cpp : include all source files
//
#include "stdafx.h"

#ifdef __NANA_RUNNER_LIB_ALL_IN_ONE
#undef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/_config.cpp>
#include <runa/base/base.cpp>
#include <runa/base/object.cpp>

#include <runa/base/dumper.cpp>
#include <runa/base/node.cpp>
#include <runa/base/parser.cpp>

#include <runa/base/log.cpp>

#include <runa/base/mt_thread.cpp>

#include <runa/base/bytes.cpp>
#include <runa/base/datetime.cpp>
#include <runa/base/id.cpp>
#include <runa/base/istr.cpp>

#include <runa/base/cmdargs.cpp>
#include <runa/base/util.cpp>

#include <runa/foundation/app_base.cpp>
#include <runa/foundation/controller_base.cpp>
#include <runa/foundation/model_base.cpp>
#include <runa/foundation/view_base.cpp>
#include <runa/foundation/view_factory.cpp>
#include <runa/foundation/widget_base.cpp>
#include <runa/foundation/widget_cfg.cpp>
#include <runa/foundation/widget_factory.cpp>

#include <runa/foundation/font/font_model.cpp>
#include <runa/foundation/font/font_view_impl.cpp>

#include <runa/foundation/color/color_chooser.cpp>
#include <runa/foundation/color/color_cntrl.cpp>
#include <runa/foundation/color/color_hsl.cpp>
#include <runa/foundation/color/color_hsv.cpp>
#include <runa/foundation/color/color_model.cpp>
#include <runa/foundation/color/color_rgb.cpp>
#include <runa/foundation/color/color_view_impl.cpp>

#include <runa/widgets/button_cfg.cpp>
#include <runa/widgets/categorize_cfg.cpp>
#include <runa/widgets/checkbox_cfg.cpp>
#include <runa/widgets/color_chooser_cfg.cpp>
#include <runa/widgets/combox_cfg.cpp>
#include <runa/widgets/form_cfg.cpp>
#include <runa/widgets/group_cfg.cpp>
#include <runa/widgets/label_cfg.cpp>
#include <runa/widgets/listbox_cfg.cpp>
#include <runa/widgets/menu_cfg.cpp>
#include <runa/widgets/menubar_cfg.cpp>
#include <runa/widgets/panel_cfg.cpp>
#include <runa/widgets/panel_lite_cfg.cpp>
#include <runa/widgets/picture_cfg.cpp>
#include <runa/widgets/progress_cfg.cpp>
#include <runa/widgets/radiobox_cfg.cpp>
#include <runa/widgets/scroll_cfg.cpp>
#include <runa/widgets/slider_cfg.cpp>
#include <runa/widgets/spinbox_cfg.cpp>
#include <runa/widgets/tab_cfg.cpp>
#include <runa/widgets/tabbar_cfg.cpp>
#include <runa/widgets/textbox_cfg.cpp>
#include <runa/widgets/toolbar_cfg.cpp>
#include <runa/widgets/treebox_cfg.cpp>
#include <runa/widgets/widget_all.cpp>

#endif

