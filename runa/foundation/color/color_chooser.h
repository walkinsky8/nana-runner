/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/01/03
#pragma once

#include <nana/gui/widgets/widget.hpp>

#include <runa/foundation/color/color_chooser_base.h>
#include <runa/foundation/color/color_abc.h>

namespace runa
{
    class color_chooser;

	namespace drawerbase
	{
		namespace color_chooser
		{
			struct color_chooser_events
				: public nana::general_events
			{
				nana::basic_event<arg_color_chooser> color_changed;
			};

            enum class buttons
            {
                none, ab_part, c_part, sample_part
            };

            struct metrics_type
            {
                using value_type = color_abc;
                value_type value{};
                color_mode mode{ color_mode::rgb };

                buttons what{ buttons::none};
                bool pressed{ false };

                metrics_type() {
                }

                bool operator!=(const metrics_type& _other) const
                {
                    return value != _other.value || mode != _other.mode;
                }
                bool operator==(const metrics_type& _other) const
                {
                    return !(*this != _other);
                }
            };

            class drawer
			{
                using value_type = metrics_type::value_type;

			public:
				using graph_reference = nana::paint::graphics&;
                
                constexpr static int ab_left = 0;
                constexpr static int ab_top = 0;
                constexpr static uint ab_width = 256;
                constexpr static uint ab_height = 256;
                constexpr static int ab_right = ab_left + ab_width;
                constexpr static int ab_bottom = ab_top + ab_height;
                constexpr static int sep = 10;
                constexpr static int sample_left = ab_right + sep;
                constexpr static int sample_top = ab_top;
                constexpr static uint sample_width = 40;
                constexpr static uint sample_height = ab_height;
                constexpr static int sample_right = sample_left + sample_width;
                constexpr static int sample_bottom = sample_top + sample_height;
                constexpr static int c_left = ab_left;
                constexpr static int c_top = ab_bottom + sep;
                constexpr static uint c_width = ab_width + sep + sample_width;
                constexpr static uint c_height = 20;
                constexpr static int c_right = c_left + c_width;
                constexpr static int c_bottom = c_top + c_height;

				drawer(metrics_type& m);
                void attach(nana::window _wnd);
                buttons what(graph_reference, const nana::point&);
                bool update_value(buttons, const nana::point&);
                void draw(graph_reference);

			private:
                void _m_draw_color(graph_reference, buttons what);
                void _m_draw_cursor(graph_reference, buttons what);

            private:
                metrics_type &metrics_;
                nana::window wnd_{};
            };

			class trigger
				: public nana::drawer_trigger
			{
                using value_type = metrics_type::value_type;

			public:
                trigger();

                void set_value(color_mode _mode, color_abc const& _value);
                void set_value(color_mode _mode, color const& _value);
                void set_value(color_mode _mode, string const& _value);

                const metrics_type& metrics() const;

                value_type value() const;

                string to_string() const;

                color to_color() const;

                color_mode mode() const;

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
                runa::color_chooser * widget_{};
                nana::paint::graphics * graph_{};
				metrics_type metrics_;
				drawer	drawer_;

            }; //end class trigger

		}//end namespace color_chooser

	}//end namespace drawerbase

	class color_chooser
        : public nana::widget_object<nana::category::widget_tag, drawerbase::color_chooser::trigger, drawerbase::color_chooser::color_chooser_events>
	{
        using self_type = color_chooser;
        using base_type = nana::widget_object<nana::category::widget_tag, drawerbase::color_chooser::trigger, drawerbase::color_chooser::color_chooser_events>;
        using value_type = color_abc;

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

        void set_value(color_mode _mode, color_abc const& _value)
        {
            this->get_drawer_trigger().set_value(_mode, _value);
        }

        void set_value(color_mode _mode, color const& _value)
        {
            this->get_drawer_trigger().set_value(_mode, _value);
        }

        void set_value(color_mode _mode, string const& _value)
        {
            this->get_drawer_trigger().set_value(_mode, _value);
        }

        const value_type& value() const
		{
			return this->get_drawer_trigger().value();
		}

        string to_string() const
        {
            return this->get_drawer_trigger().to_string();
        }

        color to_color() const
        {
            return this->get_drawer_trigger().to_color();
        }

        color_mode mode() const
        {
            return this->get_drawer_trigger().mode();
        }

        nana::window window_handle() const
		{
			return this->handle();
		}

    };//end class color_chooser

    inline void operator>>(const color_chooser& _is, string& _v)
    {
        _v = _is.to_string();
    }

    inline void operator>>(const color_chooser& _is, color& _v)
    {
        _v = _is.to_color();
    }

}//end namespace runa

