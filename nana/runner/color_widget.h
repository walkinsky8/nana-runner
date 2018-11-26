// Created by walkinsky(lyh6188@hotmail.com), 2018/11/25
#pragma once

#include <nana/gui/widgets/widget.hpp>
#include <type_traits>

namespace runa
{
	namespace drawerbase
	{
		namespace color_widget
		{
			class drawer: public nana::drawer_trigger
			{
				void attached(widget_reference, graph_reference)	override;
				void refresh(graph_reference)	override;
			private:
				nana::window window_{nullptr};
			};
		}
	}

	class color_widget
		: public nana::widget_object<nana::category::widget_tag, drawerbase::color_widget::drawer>
	{
        double h_{0}; // 0..360
        double s_{0}; // 0..1
        double l_{0}; // 0..1

    public:
        color_widget(){}

        color_widget(nana::window wd, bool visible)
		{
			this->create(wd, nana::rectangle(), visible);
			this->bgcolor(nana::API::bgcolor(wd));
		}

        color_widget(nana::window wd, const nana::rectangle& r = nana::rectangle(), bool visible = true)
		{
			this->create(wd, r, visible);
			this->bgcolor(nana::API::bgcolor(wd));
		}

        double h() const { return h_; }
        double s() const { return s_; }
        double l() const { return l_; }

        void set_hsl(double _h, double _s, double _l);

	};

}

