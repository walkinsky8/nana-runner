// Created by walkinsky(lyh6188@hotmail.com), 2018/12/12
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
        nana::color value;

		arg_color_chooser(nana::window wd, nana::color _value)
            : window_handle{ wd }, value{ _value }
		{}
	};

}//end namespace runa

