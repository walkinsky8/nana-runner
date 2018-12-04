// Created by walkinsky(lyh6188@hotmail.com), 2018/12/03
#pragma once

#include <nana/gui/widgets/widget.hpp>

#include <nana/runner/color_rgb.h>

namespace runa
{
    class color_rgb_chooser;

	struct arg_color_rgb_chooser
		: public nana::event_arg
	{
		nana::window window_handle;

		arg_color_rgb_chooser(nana::window wd)
			: window_handle{ wd }
		{}
	};

	namespace drawerbase
	{
		namespace color_rgb_chooser
		{
			struct color_rgb_chooser_events
				: public nana::general_events
			{
				nana::basic_event<arg_color_rgb_chooser> value_changed;
			};

            enum class buttons
            {
                none, rg_part, b_part, sample_part
            };

            struct metrics_type
            {
                using value_type = color_rgb;
                value_type value{};

                buttons what{ buttons::none};
                bool pressed{ false };

                metrics_type() {}
            };

            class drawer
			{
                using value_type = metrics_type::value_type;

			public:
				using graph_reference = nana::paint::graphics&;
                
                constexpr static int rg_left = 0;
                constexpr static int rg_top = 0;
                constexpr static uint rg_width = 256;
                constexpr static uint rg_height = 256;
                constexpr static int rg_right = rg_left + rg_width;
                constexpr static int rg_bottom = rg_top + rg_height;
                constexpr static int sep = 10;
                constexpr static int sample_left = rg_right + sep;
                constexpr static int sample_top = rg_top;
                constexpr static uint sample_width = 40;
                constexpr static uint sample_height = rg_height;
                constexpr static int sample_right = sample_left + sample_width;
                constexpr static int sample_bottom = sample_top + sample_height;
                constexpr static int b_left = rg_left;
                constexpr static int b_top = rg_bottom + sep;
                constexpr static uint b_width = rg_width + sep + sample_width;
                constexpr static uint b_height = 15;
                constexpr static int b_right = b_left + b_width;
                constexpr static int b_bottom = b_top + b_height;

				drawer(metrics_type& m);
                buttons what(graph_reference, const nana::point&);
                bool update_value(buttons, const nana::point&);
                void draw(graph_reference, buttons);

			private:
                void _m_background(graph_reference);
                void _m_draw_color(graph_reference, buttons what);
                void _m_draw_cursor(graph_reference, buttons what);

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

                bool make_step(bool forward, int _multiple, const nana::arg_wheel& arg);

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
                runa::color_rgb_chooser * widget_;
				nana::paint::graphics * graph_;
				metrics_type metrics_;
				drawer	drawer_;

            }; //end class trigger

		}//end namespace color_rgb_chooser

	}//end namespace drawerbase

	class color_rgb_chooser
        : public nana::widget_object<nana::category::widget_tag, drawerbase::color_rgb_chooser::trigger, drawerbase::color_rgb_chooser::color_rgb_chooser_events>
	{
        using self_type = color_rgb_chooser;
        using base_type = nana::widget_object<nana::category::widget_tag, drawerbase::color_rgb_chooser::trigger, drawerbase::color_rgb_chooser::color_rgb_chooser_events>;

    public:
        using value_type = color_rgb;

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

    };//end class color_rgb_chooser

}//end namespace runa

