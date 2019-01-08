// Created by walkinsky(lyh6188@hotmail.com), 2019/01/08
#pragma once

#include <nana/gui/widgets/checkbox.hpp>

namespace runa
{
	class radiobox : public nana::checkbox
	{
        using self = radiobox;
        using super = nana::checkbox;

    public:
        self()
        {
            radio(true);
        }
		self(nana::window wd, bool visible = true)
            : super(wd, visible)
		{
            radio(true);
        }
		self(nana::window wd, const nana::rectangle& r, bool visible = true)
            : super(wd, r, visible)
        {
            radio(true);
        }

    };//end class radiobox

}//end namespace runa

