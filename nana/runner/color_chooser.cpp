// Created by walkinsky(lyh6188@hotmail.com), 2018/11/28
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_chooser.h"

#include <nana/gui/element.hpp>

namespace runa
{
	namespace drawerbase
	{
		namespace color_chooser
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
                    metrics_.value.h(360.0*(pos.x - hs_left) / hs_width);
                    metrics_.value.s(1 - static_cast<double>(pos.y - hs_top) / hs_height);
                    return buttons::hs_click;
                }

                if (pos.x >= l_left && pos.y >= l_top && pos.x < l_right && pos.y < l_bottom)
                {
                    metrics_.value.l(static_cast<double>(pos.x - l_left) / l_width);
                    return buttons::l_click;
                }

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
                metrics_.value.l(static_cast<double>(pos - l_left) / l_width);
			}

			void drawer::draw(graph_reference graph, buttons what)
			{
				_m_background(graph);

                _m_draw_color(graph, buttons::hs_click);
                _m_draw_color(graph, buttons::l_click);

                _m_draw_click(graph, buttons::hs_click);
                _m_draw_click(graph, buttons::l_click);

            }
		//private:
			void drawer::_m_background(graph_reference graph)
			{
				graph.rectangle(true, {0xd0, 0xd0, 0xd0});
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
                            c.from_hsl(360.0*(h - hs_left)/hs_width, 1 - static_cast<double>(s - hs_top) / hs_height, metrics_.value.l());
                            graph.set_pixel(h, s, c);
                        }
                    }
                }
                else if (what == buttons::l_click)
                {
                    for (int l = (int)l_left; l < (int)l_right; ++l)
                    {
                        nana::color c{};
                        c.from_hsl(metrics_.value.h(), metrics_.value.s(), static_cast<double>(l-l_left) / l_width);
                        graph.line({ l, l_top }, { l, l_bottom }, c);
                    }

                    graph.rectangle({ sample_left, sample_top, sample_width, sample_height }, true, metrics_.value);
                }
            }

            void drawer::_m_draw_click(graph_reference graph, buttons what)
            {
                if (what == buttons::hs_click)
                {
                    nana::rectangle r{
                        hs_left + static_cast<int>(metrics_.value.h() / 360 * hs_width) - 5,
                        hs_top + static_cast<int>((1 - metrics_.value.s()) * hs_height) - 5,
                        10,
                        10 };
                    graph.round_rectangle(r, 5, 5, metrics_.value.to_revert_color(), false, {});
                }
                else if (what == buttons::l_click)
                {
                    nana::rectangle r{
                        l_left + static_cast<int>(metrics_.value.l() * l_width) - 5,
                        l_top - 5,
                        10,
                        10 + l_height };
                    graph.round_rectangle(r, 3, 3, metrics_.value.to_revert_color(), false, {});
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
                        value.l() += static_cast<double>(_multiple) / drawer::l_width;
                        if (value.l() > 1.0)
                            value.l() = 1.0;
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
                        value.l() -= static_cast<double>(_multiple) / drawer::l_width;
                        if (value.l() < 0)
                            value.l() = 0;
                    }
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
                widget_ = dynamic_cast<color_widget*>(&widget);
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
                if (!metrics_.pressed)
                    return;

                bool redraw = false;
                if (metrics_.what == buttons::l_scroll)
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
	
        }//end namespace color_chooser

    }//end namespace drawerbase

}//end namespace runa

#endif

