// Created by walkinsky(lyh6188@hotmail.com), 2018/12/02
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/color/color_hsv_chooser.h>

namespace runa
{
	namespace drawerbase
	{
		namespace color_hsv_chooser
		{
		//class drawer
            double get_h(int x)
            {
                return ensure_between(360.0*(x - drawer::hs_left) / drawer::hs_width, 0.0, 360.0);
            }

            double get_s(int y)
            {
                return ensure_between(1.0 - static_cast<double>(y - drawer::hs_top) / drawer::hs_height, 0.0, 1.0);
            }

            double get_v(int x)
            {
                return ensure_between(static_cast<double>(x - drawer::v_left) / drawer::v_width, 0.0, 1.0);
            }

            int get_x_by_h(double h)
            {
                return drawer::hs_left + static_cast<int>(h / 360 * drawer::hs_width);
            }

            int get_y_by_s(double s)
            {
                return drawer::hs_top + static_cast<int>((1 - s) * drawer::hs_height);
            }

            int get_x_by_v(double v)
            {
                return drawer::v_left + static_cast<int>(v * drawer::v_width);
            }

            drawer::drawer(metrics_type& m)
				: metrics_(m)
			{}

			buttons drawer::what(graph_reference graph, const nana::point& screen_pos)
			{
                //const nana::size scale = { graph.width(), graph.height() };
                const nana::point pos = screen_pos;

                if (pt_in_rect(pos, { hs_left, hs_top, hs_width, hs_height }))
                {
                    return buttons::hs_part;
                }

                if (pt_in_rect(pos, { v_left, v_top, v_width, v_height }))
                {
                    return buttons::v_part;
                }

				return buttons::none;
			}

            bool drawer::update_value(buttons _what, const nana::point& _pos)
            {
                const value_type old = metrics_.value;
                if (_what == buttons::hs_part)
                {
                    metrics_.value.h(get_h(_pos.x));
                    metrics_.value.s(get_s(_pos.y));
                }
                else if (_what == buttons::v_part)
                {
                    metrics_.value.v(get_v(_pos.x));
                }
                return old != metrics_.value;
            }

			void drawer::draw(graph_reference graph, buttons what)
			{
				_m_background(graph);

                _m_draw_color(graph, buttons::hs_part);
                _m_draw_color(graph, buttons::v_part);
                _m_draw_color(graph, buttons::sample_part);

                _m_draw_cursor(graph, buttons::hs_part);
                _m_draw_cursor(graph, buttons::v_part);

            }
		//private:
			void drawer::_m_background(graph_reference graph)
			{
				graph.rectangle(true, {0xd0, 0xd0, 0xd0});
			}
 
            void drawer::_m_draw_color(graph_reference graph, buttons what)
            { 
                if (what == buttons::hs_part)
                {
                    for (int h = hs_left; h < hs_right; ++h)
                    {
                        for (int s = hs_top; s < hs_bottom; ++s)
                        {
                            color_hsv hsv{ get_h(h), get_s(s), metrics_.value.v() };
                            graph.set_pixel(h, s, hsv.to_color());
                        }
                    }
                }
                else if (what == buttons::v_part)
                {
                    for (int v = v_left; v < v_right; ++v)
                    {
                        color_hsv hsv{ metrics_.value.h(), metrics_.value.s(), get_v(v) };
                        graph.line({ v, v_top }, { v, v_bottom }, hsv.to_color());
                    }
                }
                else if (what == buttons::sample_part)
                {
                    graph.rectangle({ sample_left, sample_top, sample_width, sample_height }, true, metrics_.value);
                }
            }

            nana::color get_cursor_color(color_hsv value)
            {
                return value.v() < 0.5 ? nana::colors::white : nana::colors::black;
            }

            void drawer::_m_draw_cursor(graph_reference graph, buttons what)
            {
                if (what == buttons::hs_part)
                {
                    nana::rectangle r{ get_x_by_h(metrics_.value.h()) - 5, get_y_by_s(metrics_.value.s()) - 5, 10, 10 };
                    graph.round_rectangle(r, 5, 5, get_cursor_color(metrics_.value), false, {});
                }
                else if (what == buttons::v_part)
                {
                    nana::rectangle r{ get_x_by_v(metrics_.value.v()) - 5, v_top - 5, 10, 10 + v_height };
                    graph.round_rectangle(r, 3, 3, get_cursor_color(metrics_.value), false, {});
                }
            }

            //end class drawer

            //class trigger

            trigger::trigger()
                : graph_(nullptr), drawer_(metrics_)
            {
            }

            const metrics_type& trigger::metrics() const
            {
                return metrics_;
            }

            void trigger::value(value_type const& _value)
            {
                if (graph_ && (metrics_.value != _value))
                {
                    metrics_.value = _value;
                    _m_emit_value_changed();

                    nana::API::refresh_window(*widget_);
                }
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
                        value.h() += 360.0 * (_multiple) / drawer::hs_width;
                        if (value.h() > 360.0)
                            value.h() = 360.0;
                    }
                    else if (arg.shift)
                    {
                        value.s() += static_cast<double>(_multiple) / drawer::hs_height;
                        if (value.s() > 1)
                            value.s() = 1;
                    }
                    else
                    {
                        value.v() += static_cast<double>(_multiple) / drawer::v_width;
                        if (value.v() > 1.0)
                            value.v() = 1.0;
                    }
                }
                else
                {
                    if (arg.ctrl)
                    {
                        value.h() -= 360.0 * (_multiple) / drawer::hs_width;
                        if (value.h() < 0)
                            value.h() = 0;
                    }
                    else if (arg.shift)
                    {
                        value.s() -= static_cast<double>(_multiple) / drawer::hs_height;
                        if (value.s() < 0)
                            value.s() = 0;
                    }
                    else
                    {
                        value.v() -= static_cast<double>(_multiple) / drawer::v_width;
                        if (value.v() < 0)
                            value.v() = 0;
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
                widget_ = dynamic_cast<runa::color_hsv_chooser*>(&widget);
                widget.caption("runa_color_hsv_chooser");
            }

            void trigger::detached()
            {
                graph_ = nullptr;
            }

            void trigger::refresh(graph_reference graph)
            {
                drawer_.draw(graph, metrics_.what);
            }

            void trigger::resized(graph_reference graph, const ::nana::arg_resized&)
            {
                drawer_.draw(graph, metrics_.what);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_enter(graph_reference graph, const ::nana::arg_mouse& arg)
            {
                metrics_.what = drawer_.what(graph, arg.pos);
                drawer_.draw(graph, metrics_.what);
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
                    drawer_.draw(graph, metrics_.what);
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
                drawer_.draw(graph, metrics_.what);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_leave(graph_reference graph, const nana::arg_mouse&)
            {
                if (metrics_.pressed) return;

                metrics_.what = buttons::none;
                drawer_.draw(graph, buttons::none);
                nana::API::dev::lazy_refresh();
            }

            void trigger::mouse_wheel(graph_reference graph, const nana::arg_wheel& arg)
            {
                if (make_step(arg.upwards, 3, arg))
                {
                    drawer_.draw(graph, metrics_.what);
                    nana::API::dev::lazy_refresh();
                }
            }

            void trigger::_m_emit_value_changed()
            {
                widget_->events().value_changed.emit({ widget_->handle() }, widget_->handle());
            }
                
            //end class trigger
	
        }//end namespace color_hsv_chooser

    }//end namespace drawerbase

}//end namespace runa

#endif

