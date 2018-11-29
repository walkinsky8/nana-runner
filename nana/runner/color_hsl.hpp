// Created by walkinsky(lyh6188@hotmail.com), 2018/11/28
#pragma once

#include <nana/gui/widgets/widget.hpp>

namespace runa
{
    class color_hsl;
    using color_hsl_widget = color_hsl;

    struct hsl
    {
        double h{}; // 0..360
        double s{}; // 0..1
        double l{}; // 0..1

        hsl()
        {}
        hsl(double _h, double _s, double _l)
            : h{ _h }, s{ _s }, l{ _l }
        {}

        operator nana::color() const
        {
            return nana::color{}.from_hsl(h, s, l);
        }

        bool operator!=(const hsl& _v) const
        {
            return h != _v.h || s != _v.h || l != _v.l;
        }
        bool operator==(const hsl& _v) const
        {
            return !operator!=(_v);
        }

    };

	struct arg_color_hsl
		: public nana::event_arg
	{
		nana::window window_handle;

		arg_color_hsl(nana::window wd)
			: window_handle{ wd }
		{}
	};

	namespace drawerbase
	{
		namespace color_hsl
		{
			struct color_hsl_events
				: public nana::general_events
			{
				nana::basic_event<arg_color_hsl> value_changed;
			};

            enum class buttons
            {
                none, hs_click, l_click, l_scroll, l_first, l_second
            };

            struct metrics_type
            {
                using value_type = hsl;
                value_type value{};

                buttons what{ buttons::none};
                bool pressed{ false };

                metrics_type() {}
            };

            class drawer
			{
			public:
				using graph_reference = nana::paint::graphics&;
                
                constexpr static unsigned hs_left = 0;
                constexpr static unsigned hs_top = 0;
                constexpr static unsigned hs_width = 360;
                constexpr static unsigned hs_height = 200;
                constexpr static unsigned hs_right = hs_left + hs_width;
                constexpr static unsigned hs_bottom = hs_top + hs_height;
                constexpr static unsigned sep = 10;
                constexpr static unsigned fixedsize = 16;
                constexpr static unsigned l_left = hs_left + fixedsize;
                constexpr static unsigned l_top = hs_top + hs_height + sep;
                constexpr static unsigned l_width = 360 - fixedsize * 2;
                constexpr static unsigned l_height = 20;
                constexpr static unsigned l_right = l_left + l_width;
                constexpr static unsigned l_bottom = l_top + l_height;
                constexpr static unsigned sample_height = 20;

				drawer(metrics_type& m);
                buttons what(graph_reference, const nana::point&);
                void scroll_delta_pos(graph_reference, int);
                void draw(graph_reference, buttons);

			private:
                void _m_background(graph_reference);
                void _m_draw_color(graph_reference, buttons what);
                void _m_draw_button(graph_reference, ::nana::rectangle, buttons what);
                void _m_draw_click(graph_reference, ::nana::rectangle, buttons what);

            private:
                metrics_type &metrics_;

            };

			class trigger
				: public nana::drawer_trigger
			{
                using value_type = metrics_type::value_type;

			public:
                trigger();

                const metrics_type& metrics() const;

                void value(value_type const& _value);

                bool make_step(bool forward, int _multiple);

			private:
                void attached(widget_reference widget, graph_reference graph) override;

                void detached() override;

                void refresh(graph_reference graph) override;

                void resized(graph_reference graph, const ::nana::arg_resized&) override;

                void mouse_enter(graph_reference graph, const ::nana::arg_mouse& arg) override;

                void mouse_move(graph_reference graph, const ::nana::arg_mouse& arg) override;

                void dbl_click(graph_reference graph, const nana::arg_mouse& arg) override;

                void mouse_down(graph_reference graph, const nana::arg_mouse& arg) override;

                void mouse_up(graph_reference graph, const nana::arg_mouse& arg) override;

                void mouse_leave(graph_reference graph, const nana::arg_mouse&) override;

                void mouse_wheel(graph_reference graph, const nana::arg_wheel& arg) override;

			private:
                void _m_emit_value_changed();

			private:
                color_hsl_widget * widget_;
				nana::paint::graphics * graph_;
				metrics_type metrics_;
				drawer	drawer_;

            }; //end class trigger

		}//end namespace color_hsl

	}//end namespace drawerbase

	class color_hsl
        : public nana::widget_object<nana::category::widget_tag, drawerbase::color_hsl::trigger, drawerbase::color_hsl::color_hsl_events>
	{
        using self_type = color_hsl;
        using base_type = nana::widget_object<nana::category::widget_tag, drawerbase::color_hsl::trigger, drawerbase::color_hsl::color_hsl_events>;
        using value_type = hsl;

    public:
        self_type()
        {
        }
		self_type(nana::window wd, bool visible = true)
		{
			this->create(wd, nana::rectangle(), visible);
		}
		self_type(nana::window wd, const nana::rectangle& r, bool visible = true)
		{
			this->create(wd, r, visible);
		}

		const value_type& value() const
		{
			return this->get_drawer_trigger().metrics().value;
		}

		void value(const value_type& v)
		{
			return this->get_drawer_trigger().value(v);
		}

		nana::window window_handle() const
		{
			return this->handle();
		}

    };//end class color_hsl

}//end namespace runa

