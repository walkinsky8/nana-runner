// Created by walkinsky(lyh6188@hotmail.com), 2018/11/28
#pragma once

#include <nana/gui/widgets/widget.hpp>

namespace runa
{
    class color_chooser;
    using color_widget = color_chooser;

    struct hsl
    {
        double h{}; // 0..360
        double s{1}; // 0..1
        double l{0.5}; // 0..1

        hsl()
        {}
        hsl(double _h, double _s, double _l)
            : h{ _h }, s{ _s }, l{ _l }
        {}

        operator nana::color() const
        {
            return to_color();
        }

        nana::color to_color() const
        {
            return nana::color{}.from_hsl(h, s, l);
        }

        nana::color to_revert_color() const
        {
            nana::color c{};
            c.from_hsl(h, s, l);
            return nana::color{ static_cast<uint>(255 - c.r()), static_cast<uint>(255 - c.g()), static_cast<uint>(255 - c.b()) };
        }

        bool operator!=(const hsl& _v) const
        {
            return h != _v.h || s != _v.s || l != _v.l;
        }
        bool operator==(const hsl& _v) const
        {
            return !operator!=(_v);
        }

    };

	struct arg_color_chooser
		: public nana::event_arg
	{
		nana::window window_handle;

		arg_color_chooser(nana::window wd)
			: window_handle{ wd }
		{}
	};

	namespace drawerbase
	{
		namespace color_chooser
		{
			struct color_chooser_events
				: public nana::general_events
			{
				nana::basic_event<arg_color_chooser> value_changed;
			};

            enum class buttons
            {
                none, hs_click, l_click, l_scroll
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
                
                constexpr static int hs_left = 0;
                constexpr static int hs_top = 0;
                constexpr static uint hs_width = 255;
                constexpr static uint hs_height = 255;
                constexpr static int hs_right = hs_left + hs_width;
                constexpr static int hs_bottom = hs_top + hs_height;
                constexpr static int sep = 15;
                constexpr static int sample_left = hs_right + sep;
                constexpr static int sample_top = hs_top;
                constexpr static uint sample_width = 40;
                constexpr static uint sample_height = hs_height;
                constexpr static int sample_right = sample_left + sample_width;
                constexpr static int sample_bottom = sample_top + sample_height;
                constexpr static int l_left = hs_left;
                constexpr static int l_top = hs_bottom + sep;
                constexpr static uint l_width = hs_width + sep + sample_width;
                constexpr static uint l_height = 15;
                constexpr static int l_right = l_left + l_width;
                constexpr static int l_bottom = l_top + l_height;

				drawer(metrics_type& m);
                buttons what(graph_reference, const nana::point&);
                void scroll_delta_pos(graph_reference, int);
                void draw(graph_reference, buttons);

			private:
                void _m_background(graph_reference);
                void _m_draw_color(graph_reference, buttons what);
                void _m_draw_click(graph_reference, buttons what);

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
                color_widget * widget_;
				nana::paint::graphics * graph_;
				metrics_type metrics_;
				drawer	drawer_;

            }; //end class trigger

		}//end namespace color_hsl

	}//end namespace drawerbase

	class color_chooser
        : public nana::widget_object<nana::category::widget_tag, drawerbase::color_chooser::trigger, drawerbase::color_chooser::color_chooser_events>
	{
        using self_type = color_chooser;
        using base_type = nana::widget_object<nana::category::widget_tag, drawerbase::color_chooser::trigger, drawerbase::color_chooser::color_chooser_events>;
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

