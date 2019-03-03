/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/01/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_chooser.h>
#include <runa/foundation/color/color_rgb.h>
#include <runa/foundation/color/color_hsl.h>
#include <runa/foundation/color/color_hsv.h>

namespace runa
{
	namespace drawerbase
	{
		namespace color_chooser
		{
            class color_value_factor
            {
                using self = color_value_factor;

                double a_{};
                double b_{};
                double c_{};

            public:
                color_value_factor()
                {}
                color_value_factor(double _a, double _b, double _c)
                    : a_{ _a }, b_{ _b }, c_{ _c }
                {}

                double a() const
                {
                    return a_;
                }
                double& a()
                {
                    return a_;
                }
                self& a(double _a)
                {
                    a_ = _a;
                    return *this;
                }

                double b() const
                {
                    return b_;
                }
                double& b()
                {
                    return b_;
                }
                self& b(double _b)
                {
                    b_ = _b;
                    return *this;
                }

                double c() const
                {
                    return c_;
                }
                double& c()
                {
                    return c_;
                }
                self& c(double _c)
                {
                    c_ = _c;
                    return *this;
                }

                bool operator!=(const self& _v) const
                {
                    return a_ != _v.a_ || b_ != _v.b_ || c_ != _v.c_;
                }
                bool operator==(const self& _v) const
                {
                    return !operator!=(_v);
                }

            };

            class color_rgb_factor : public color_value_factor
            {
            public:
                color_rgb_factor() : color_value_factor{ 255, 255, 255 }
                {}
            };

            class color_hsl_factor : public color_value_factor
            {
            public:
                color_hsl_factor() : color_value_factor{ 360, 1, 1 }
                {}
            };

            class color_hsv_factor : public color_value_factor
            {
            public:
                color_hsv_factor() : color_value_factor{ 360, 1, 1 }
                {}
            };

            class color_value : public color_value_factor
            {
                using self = color_value;
                using super = color_value_factor;

            public:
                color_value()
                {}
                color_value(super const& _value)
                    : super{ _value }
                {}
                color_value(double _a, double _b, double _c)
                    : super{ _a,_b,_c }
                {}
                color_value(const color_rgb& _v)
                    : super{_v.r(), _v.g(), _v.b()}
                {}
                color_value(const color_hsl& _v)
                    : super{ _v.h(), _v.s(), _v.l() }
                {}
                color_value(const color_hsv& _v)
                    : super{ _v.h(), _v.s(), _v.v() }
                {}

                color to_color(color_mode _mode) const
                {
                    switch (_mode)
                    {
                    case color_mode::rgb:
                        return color_rgb{ a(), b(), c() }.to_color();
                    case color_mode::hsl:
                        return color_hsl{ a(), b(), c() }.to_color();
                    case color_mode::hsv:
                        return color_hsv{ a(), b(), c() }.to_color();
                    }
                    return {};
                }

                static self from_color(const color& _v, color_mode _mode)
                {
                    switch (_mode)
                    {
                    case color_mode::rgb:
                        return self{ color_rgb::from_color(_v) };
                    case color_mode::hsl:
                        return self{ color_hsl::from_color(_v) };
                    case color_mode::hsv:
                        return self{ color_hsv::from_color(_v) };
                    }
                    return {};
                }

                string to_string(color_mode _mode) const
                {
                    switch (_mode)
                    {
                    case color_mode::rgb:
                        return color_rgb{ a(), b(), c() }.str();
                    case color_mode::hsl:
                        return color_hsl{ a(), b(), c() }.str();
                    case color_mode::hsv:
                        return color_hsv{ a(), b(), c() }.str();
                    }
                    return {};
                }

                static self from_string(const string& _v, color_mode _mode)
                {
                    switch (_mode)
                    {
                    case color_mode::rgb:
                        return self{ color_rgb::from_string(_v) };
                    case color_mode::hsl:
                        return self{ color_hsl::from_string(_v) };
                    case color_mode::hsv:
                        return self{ color_hsv::from_string(_v) };
                    }
                    return {};
                }

            };

            inline color_value operator*(color_value_factor const& _x, color_abc const& _y)
            {
                return { _x.a()*_y.a(), _x.b()*_y.b(), _x.c()*_y.c() };
            }

            inline color_value operator*(color_abc const& _x, color_value_factor const& _y)
            {
                return { _x.a()*_y.a(), _x.b()*_y.b(), _x.c()*_y.c() };
            }

            inline color_abc operator/(color_value const& _x, color_value_factor const& _y)
            {
                return { _x.a()/_y.a(), _x.b()/_y.b(), _x.c()/_y.c() };
            }

            inline color_value_factor get_factor(color_mode _mode)
            {
                return _mode == color_mode::rgb ? color_rgb_factor() :
                    _mode == color_mode::hsl ? color_hsl_factor() :
                    _mode == color_mode::hsv ? color_hsv_factor() :
                    color_value_factor{ 1, 1, 1 };
            }

            color to_color(color_abc const& _abc, color_mode _mode)
            {
                const auto factor = get_factor(_mode);
                const auto value = _abc * factor;
                return value.to_color(_mode);
            }

            color_abc from_color(color const& _clr, color_mode _mode)
            {
                const auto factor = get_factor(_mode);
                const auto value = color_value::from_color(_clr, _mode);
                return value / factor;
            }

            string to_string(color_abc const& _abc, color_mode _mode)
            {
                const auto factor = get_factor(_mode);
                const auto value = _abc * factor;
                return value.to_string(_mode);
            }

            color_abc from_string(string const& _clr, color_mode _mode)
            {
                const auto factor = get_factor(_mode);
                const auto value = color_value::from_string(_clr, _mode);
                return value / factor;
            }

            double get_a(int x)
            {
                return ensure_between(static_cast<double>(x - drawer::ab_left) / drawer::ab_width, 0.0, 1.0);
            }

            double get_b(int y)
            {
                return ensure_between(1.0 - static_cast<double>(y - drawer::ab_top) / drawer::ab_height, 0.0, 1.0);
            }

            double get_c(int x)
            {
                return ensure_between(static_cast<double>(x - drawer::c_left) / drawer::c_width, 0.0, 1.0);
            }

            int get_x_by_a(double a)
            {
                return drawer::ab_left + static_cast<int>(a * drawer::ab_width);
            }

            int get_y_by_b(double b)
            {
                return drawer::ab_top + static_cast<int>((1.0 - b) * drawer::ab_height);
            }

            int get_x_by_c(double c)
            {
                return drawer::c_left + static_cast<int>(c * drawer::c_width);
            }

            //class drawer

            drawer::drawer(metrics_type& m)
				: metrics_(m)
			{}

            void drawer::attach(nana::window _wnd)
            {
                wnd_ = _wnd;
            }

			buttons drawer::what(graph_reference graph, const nana::point& screen_pos)
			{
                //const nana::size scale = { graph.width(), graph.height() };
                const nana::point pos = screen_pos;

                if (pt_in_rect(pos, { ab_left, ab_top, ab_width, ab_height }))
                {
                    return buttons::ab_part;
                }

                if (pt_in_rect(pos, { c_left, c_top, c_width, c_height }))
                {
                    return buttons::c_part;
                }

				return buttons::none;
			}

            bool drawer::update_value(buttons _what, const nana::point& _pos)
            {
                const auto old = metrics_;
                if (_what == buttons::ab_part)
                {
                    metrics_.value.a(get_a(_pos.x));
                    metrics_.value.b(get_b(_pos.y));
                }
                else if (_what == buttons::c_part)
                {
                    metrics_.value.c(get_c(_pos.x));
                }
                return old != metrics_;
            }

			void drawer::draw(graph_reference graph)
			{
                graph.rectangle(true, nana::API::bgcolor(wnd_));

                _m_draw_color(graph, buttons::ab_part);
                _m_draw_color(graph, buttons::c_part);
                _m_draw_color(graph, buttons::sample_part);

                _m_draw_cursor(graph, buttons::ab_part);
                _m_draw_cursor(graph, buttons::c_part);
            }

		//private:
            
            void drawer::_m_draw_color(graph_reference graph, buttons what)
            { 
                if (what == buttons::ab_part)
                {
                    for (int x = ab_left; x < ab_right; ++x)
                    {
                        for (int y = ab_top; y < ab_bottom; ++y)
                        {
                            graph.set_pixel(x, y, to_color({ get_a(x), get_b(y), metrics_.value.c() }, metrics_.mode));
                        }
                    }
                }
                else if (what == buttons::c_part)
                {
                    for (int x = c_left; x < c_right; ++x)
                    {
                        graph.line({ x, c_top }, { x, c_bottom }, to_color({ metrics_.value.a(), metrics_.value.b(), get_c(x) }, metrics_.mode));
                    }
                }
                else if (what == buttons::sample_part)
                {
                    graph.rectangle({ sample_left, sample_top, sample_width, sample_height }, true, to_color(metrics_.value, metrics_.mode));
                }
            }

            nana::color get_cursor_color(color_abc value)
            {
                return value.c() < 0.5 ? nana::colors::white : nana::colors::black;
            }

            void drawer::_m_draw_cursor(graph_reference graph, buttons what)
            {
                if (what == buttons::ab_part)
                {
                    nana::rectangle r{ get_x_by_a(metrics_.value.a()) - 5, get_y_by_b(metrics_.value.b()) - 5, 10, 10 };
                    graph.round_rectangle(r, 5, 5, get_cursor_color(metrics_.value), false, {});
                }
                else if (what == buttons::c_part)
                {
                    nana::rectangle r{ get_x_by_c(metrics_.value.c()) - 5, c_top - 5, 10, 10 + c_height };
                    graph.round_rectangle(r, 3, 3, get_cursor_color(metrics_.value), false, {});
                }
            }

            //end class drawer

            //class trigger

            trigger::trigger()
                : graph_(nullptr), drawer_(metrics_)
            {
            }

            void trigger::set_value(color_mode _mode, color_abc const& _value)
            {
                if (graph_)
                {
                    const auto old = metrics_;
                    metrics_.mode = _mode;
                    metrics_.value = _value;
                    if (old != metrics_)
                    {
                        _m_emit_value_changed();
                        nana::API::refresh_window(*widget_);
                    }
                }
            }

            void trigger::set_value(color_mode _mode, color const& _value)
            {
                set_value(_mode, color_chooser::from_color(_value, _mode));
            }

            void trigger::set_value(color_mode _mode, string const& _value)
            {
                set_value(_mode, color_chooser::from_string(_value, _mode));
            }

            const metrics_type& trigger::metrics() const
            {
                return metrics_;
            }

            trigger::value_type trigger::value() const
            {
                return metrics_.value;
            }

            string trigger::to_string() const
            {
                return color_chooser::to_string(metrics_.value, metrics_.mode);
            }
            
            color trigger::to_color() const
            {
                return color_chooser::to_color(metrics_.value, metrics_.mode);
            }

            color_mode trigger::mode() const
            {
                return metrics_.mode;
            }

            bool trigger::make_step(bool forward, int _multiple, const nana::arg_wheel& arg)
            {
                if (!graph_)
                    return false;

                value_type value = metrics_.value;
                if (forward)
                {
                    if (arg.ctrl)
                    {
                        value.a() += static_cast<double>(_multiple) / drawer::ab_width;
                        if (value.a() > 1.0)
                            value.a() = 1.0;
                    }
                    else if (arg.shift)
                    {
                        value.b() += static_cast<double>(_multiple) / drawer::ab_height;
                        if (value.b() > 1.0)
                            value.b() = 1.0;
                    }
                    else
                    {
                        value.c() += static_cast<double>(_multiple) / drawer::c_width;
                        if (value.c() > 1.0)
                            value.c() = 1.0;
                    }
                }
                else
                {
                    if (arg.ctrl)
                    {
                        value.a() -= static_cast<double>(_multiple) / drawer::ab_width;
                        if (value.a() < 0)
                            value.a() = 0;
                    }
                    else if (arg.shift)
                    {
                        value.b() -= static_cast<double>(_multiple) / drawer::ab_height;
                        if (value.b() < 0)
                            value.b() = 0;
                    }
                    else
                    {
                        value.c() -= static_cast<double>(_multiple) / drawer::c_width;
                        if (value.c() < 0)
                            value.c() = 0;
                    }
                }
                if (metrics_.value != value)
                {
                    metrics_.value = value;
                    _m_emit_value_changed();
                    return true;
                }
                return false;
            }

            void trigger::attached(widget_reference widget, graph_reference graph)
            {
                graph_ = &graph;
                widget_ = dynamic_cast<runa::color_chooser*>(&widget);
                drawer_.attach(widget);
                widget.caption("runa_color_chooser");
            }

            void trigger::detached()
            {
                graph_ = nullptr;
            }

            void trigger::refresh(graph_reference graph)
            {
                drawer_.draw(graph);
            }

            void trigger::resized(graph_reference graph, const ::nana::arg_resized&)
            {
                drawer_.draw(graph);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_enter(graph_reference graph, const ::nana::arg_mouse& arg)
            {
                metrics_.what = drawer_.what(graph, arg.pos);
                drawer_.draw(graph);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_move(graph_reference graph, const ::nana::arg_mouse& arg)
            {
            }

            void trigger::dbl_click(graph_reference graph, const nana::arg_mouse& arg)
            {
                mouse_down(graph, arg);
            }

            void trigger::mouse_down(graph_reference graph, const nana::arg_mouse& arg)
            {
                if (arg.left_button)
                {
                    metrics_.pressed = true;
                    metrics_.what = drawer_.what(graph, arg.pos);
                    if (drawer_.update_value(metrics_.what, arg.pos))
                        _m_emit_value_changed();
                    drawer_.draw(graph);
                    nana::API::dev::lazy_refresh();
                }
            }

            void trigger::mouse_up(graph_reference graph, const nana::arg_mouse& arg)
            {
                widget_->release_capture();

                metrics_.pressed = false;
                metrics_.what = drawer_.what(graph, arg.pos);
                if (drawer_.update_value(metrics_.what, arg.pos))
                    _m_emit_value_changed();
                drawer_.draw(graph);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_leave(graph_reference graph, const nana::arg_mouse&)
            {
                if (metrics_.pressed) return;

                metrics_.what = buttons::none;
                drawer_.draw(graph);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_wheel(graph_reference graph, const nana::arg_wheel& arg)
            {
                if (make_step(arg.upwards, 3, arg))
                {
                    drawer_.draw(graph);
                    nana::API::dev::lazy_refresh();
                }
            }

            void trigger::_m_emit_value_changed()
            {
                widget_->events().color_changed.emit({ widget_->handle() }, widget_->handle());
            }
                
            //end class trigger
	
        }//end namespace color_chooser

    }//end namespace drawerbase

}//end namespace runa

#endif

