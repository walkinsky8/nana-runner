// Created by walkinsky(lyh6188@hotmail.com), 2018/11/25
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_chooser.h"

namespace runa
{
	namespace drawerbase
	{
		namespace color_chooser
		{
            //class drawer

            void drawer::attached(widget_reference wdg, graph_reference)
			{
				wdg.caption("color_chooser");
				window_ = wdg.handle();

				//nana::API::ignore_mouse_focus(wdg, true);
			}

            void drawer::refresh(graph_reference g)
            {
                g.rectangle(true, nana::API::bgcolor(window_));
                for (int h = 0; h < 360; ++h)
                {
                    for (int s = 0; s < 200; ++s)
                    {
                        nana::color c{};
                        c.from_hsl(h, s / 200.0, 0.5);
                        g.set_pixel(h, s, c);
                    }
                }
                for (int l = 0; l < 200; ++l)
                {
                    nana::color c{};
                    c.from_hsl(120.0, 1.0, l / 200.0);
                    g.line({ l, 205 }, { l, 225 }, c);
                }
                g.rectangle({ 210, 205, 150, 20 }, true, nana::color{}.from_hsl(120, 1.0, 0.5));
            }

            //end class drawer

		}//end namespace color_chooser
	}//end namespace drawerbase

    void color_chooser::set_hsl(double _h, double _s, double _l)
    {
        h_ = _h;
        s_ = _s;
        l_ = _l;
        nana::API::refresh_window(handle());
    }

}//end namespace runa

#endif

