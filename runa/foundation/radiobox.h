/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2019/01/08
#pragma once

#include <nana/gui/widgets/checkbox.hpp>

namespace runa
{
	class radiobox : public nana::checkbox
	{
        using self = radiobox;
        using super = nana::checkbox;

    public:
        radiobox()
        {
            radio(true);
        }
        radiobox(nana::window wd, bool visible = true)
            : super(wd, visible)
		{
            radio(true);
        }
        radiobox(nana::window wd, const nana::rectangle& r, bool visible = true)
            : super(wd, r, visible)
        {
            radio(true);
        }

    };//end class radiobox

}//end namespace runa

