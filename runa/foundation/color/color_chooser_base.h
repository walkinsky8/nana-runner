/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/12/12
#pragma once

#include <runa/base/base.h>

#include <nana/gui/widgets/widget.hpp>

namespace runa
{
    enum class color_mode
    {
        rgb = 0,
        hsl = 1,
        hsv = 2
    };

    using enum_color_mode = enum_<color_mode, color_mode::rgb>;

	struct arg_color_chooser : public nana::event_arg
	{
		nana::window window_handle;

		arg_color_chooser(nana::window wd)
            : window_handle{ wd }
		{}
	};

}//end namespace runa

