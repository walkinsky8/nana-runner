// Created by walkinsky(lyh6188@hotmail.com), 2018/11/28
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_hsl.hpp"

#include <nana/gui/element.hpp>

namespace runa
{
	namespace drawerbase
	{
		namespace color_hsl
		{
		//class drawer
			drawer::drawer(metrics_type& m)
				: metrics_(m)
			{}

			buttons drawer::what(graph_reference graph, const nana::point& screen_pos)
			{
                const nana::size scale = { graph.width(), graph.height() };
                const nana::point pos = screen_pos;

                if (pos.x >= hs_left && pos.y >= hs_top && pos.x < hs_right && pos.y < hs_bottom)
                {
                    metrics_.value.h = pos.x - hs_left;
                    metrics_.value.s = static_cast<double>(pos.y - hs_top) / hs_height;
                    return buttons::hs_click;
                }

                if (pos.x >= l_left && pos.y >= l_top && pos.x < l_right && pos.y < l_bottom)
                {
                    metrics_.value.l = static_cast<double>(pos.x - l_left) / l_width;
                    return buttons::l_click;
                }

                if (pos.x >= hs_left && pos.x < l_left && pos.y >= l_top && pos.y < l_bottom)
                    return buttons::l_first;
                
                if (pos.x >= l_right && pos.x < (l_right + fixedsize) && pos.y >= l_top && pos.y < l_bottom)
                    return buttons::l_second;

                if ((pos.y < l_top || pos.y >= l_bottom) && pos.x >= l_left && pos.x < l_right)
                    return buttons::l_scroll;

				return buttons::none;
			}

			void drawer::scroll_delta_pos(graph_reference graph, int mouse_pos)
			{
                int pos = mouse_pos;
                if (pos < l_left)
                    pos = l_left;
                if (pos > l_right)
                    pos = l_right;
                metrics_.value.l = static_cast<double>(pos - l_left) / l_width;
			}

			void drawer::draw(graph_reference graph, buttons what)
			{
				_m_background(graph);

                nana::rectangle hs_rect{ (int)hs_left, (int)hs_top, hs_width, hs_height };
                nana::rectangle l_rect{ (int)l_left, (int)l_top, l_width, l_height };
                nana::rectangle l_first_rect{ (int)hs_left, (int)l_top, fixedsize, l_height };
                nana::rectangle l_second_rect{ (int)l_right, (int)l_top, fixedsize, l_height };

                _m_draw_color(graph, buttons::hs_click);
                _m_draw_color(graph, buttons::l_click);

                _m_draw_click(graph, hs_rect, buttons::hs_click);
                _m_draw_click(graph, l_rect, buttons::l_click);

                _m_draw_button(graph, l_first_rect, buttons::l_first);
                _m_draw_button(graph, l_second_rect, buttons::l_second);

            }
		//private:
			void drawer::_m_background(graph_reference graph)
			{
				graph.rectangle(true, {0xf0, 0xf0, 0xf0});
			}

            void drawer::_m_draw_color(graph_reference graph, buttons what)
            {
                if (what == buttons::hs_click)
                {
                    for (int h = hs_left; h < hs_right; ++h)
                    {
                        for (int s = hs_top; s < hs_bottom; ++s)
                        {
                            nana::color c{};
                            c.from_hsl(360.0*(h - hs_left)/hs_width, static_cast<double>(s - hs_top) / hs_height, metrics_.value.l);
                            graph.set_pixel(h, s, c);
                        }
                    }
                }

                if (what == buttons::l_click)
                {
                    for (int l = (int)l_left; l < (int)l_right; ++l)
                    {
                        nana::color c{};
                        c.from_hsl(metrics_.value.h, metrics_.value.s, static_cast<double>(l-l_left) / l_width);
                        graph.line({ l, (int)l_top }, { l, (int)l_bottom }, c);
                    }

                    graph.rectangle({ (int)hs_left, (int)(l_bottom + sep), hs_width, sample_height }, true, metrics_.value);
                }
            }

            void drawer::_m_draw_button(graph_reference graph, nana::rectangle r, buttons what)
			{
				if(buttons::l_first == what || buttons::l_second == what)
				{
					auto sz = graph.size();
					int top = static_cast<int>(sz.height - fixedsize);
					int left = static_cast<int>(sz.width - fixedsize);

					nana::direction dir;
					if (buttons::l_second == what)
					{
						r.x = left;
						dir = nana::direction::east;
					}
					else
						dir = nana::direction::west;

				    r.y = top / 2;

					r.width = r.height = fixedsize;

					nana::facade<nana::element::arrow> arrow("solid_triangle");
					arrow.direction(dir);
					arrow.draw(graph, {}, nana::colors::black, r, nana::element_state::normal);
				}
			}
            
            void drawer::_m_draw_click(graph_reference graph, nana::rectangle r, buttons what)
            {
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

            bool trigger::make_step(bool forward, int _multiple)
            {
                if (!graph_)
                    return false;

                value_type value = metrics_.value;
                if (forward)
                {
                    value.l += _multiple;
                    if (value.l > drawer::l_width)
                        value.l = drawer::l_width;
                }
                else
                {
                    if (value.l > _multiple)
                        value.l -= _multiple;
                    else
                        value.l = 0;
                }
                value_type cmpvalue = metrics_.value;
                metrics_.value = value;
                if (value != cmpvalue)
                {
                    _m_emit_value_changed();
                    return true;
                }
                return false;
            }

            void trigger::attached(widget_reference widget, graph_reference graph)
            {
                graph_ = &graph;
                widget_ = dynamic_cast<color_hsl_widget*>(&widget);
                widget.caption("runa_color_hsl");
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
                bool redraw = false;
                if (metrics_.pressed && (metrics_.what == buttons::l_scroll))
                {
                    value_type cmpvalue = metrics_.value;
                    drawer_.scroll_delta_pos(graph, arg.pos.x);
                    if (cmpvalue != metrics_.value)
                        _m_emit_value_changed();
                    redraw = true;
                }
                else
                {
                    value_type cmpvalue = metrics_.value;
                    buttons what = drawer_.what(graph, arg.pos);
                    if (cmpvalue != metrics_.value)
                        _m_emit_value_changed();
                    if (metrics_.what != what)
                    {
                        redraw = true;
                        metrics_.what = what;
                    }
                }
                if (redraw)
                {
                    drawer_.draw(graph, metrics_.what);
                    nana::API::dev::lazy_refresh();
                }
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
                    value_type cmpvalue = metrics_.value;
                    metrics_.what = drawer_.what(graph, arg.pos);
                    if (cmpvalue != metrics_.value)
                        _m_emit_value_changed();
                    switch (metrics_.what)
                    {
                    case buttons::l_first:
                    case buttons::l_second:
                        make_step(metrics_.what == buttons::l_second, 1);
                        break;
                    case buttons::l_scroll:
                        widget_->set_capture(true);
                        break;
                    default:
                        break;
                    }
                    drawer_.draw(graph, metrics_.what);
                    nana::API::dev::lazy_refresh();
                }
            }

            void trigger::mouse_up(graph_reference graph, const nana::arg_mouse& arg)
            {
                widget_->release_capture();

                metrics_.pressed = false;
                metrics_.what = drawer_.what(graph, arg.pos);
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
                if (make_step(arg.upwards == false, 3))
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
	
        }//end namespace color_hsl

    }//end namespace drawerbase

}//end namespace runa

#endif

