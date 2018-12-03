// Created by walkinsky(lyh6188@hotmail.com), 2018/12/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_rgb_chooser.h"

namespace runa
{
	namespace drawerbase
	{
		namespace color_rgb_chooser
		{
		//class drawer
            uint get_r(int x)
            {
                return ensure_between<uint>(255 * (x - drawer::rg_left) / drawer::rg_width, 0, 255);
            }

            uint get_g(int y)
            {
                return ensure_between<uint>(255 - 255 * (y - drawer::rg_top) / drawer::rg_height, 0, 255);
            }

            uint get_b(int x)
            {
                return ensure_between<uint>(255 * (x - drawer::b_left) / drawer::b_width, 0, 255);
            }

            int get_x_by_r(uint r)
            {
                return drawer::rg_left + r * drawer::rg_width / 255;
            }

            int get_y_by_g(uint g)
            {
                return drawer::rg_top + (255 - g) * drawer::rg_height / 255;
            }

            int get_x_by_b(uint b)
            {
                return drawer::b_left + b * drawer::b_width / 255;
            }

            drawer::drawer(metrics_type& m)
				: metrics_(m)
			{}

			buttons drawer::what(graph_reference graph, const nana::point& screen_pos)
			{
                //const nana::size scale = { graph.width(), graph.height() };
                const nana::point pos = screen_pos;

                if (pt_in_rect(pos, { rg_left, rg_top, rg_width, rg_height }))
                {
                    return buttons::rg_part;
                }

                if (pt_in_rect(pos, { b_left, b_top, b_width, b_height }))
                {
                    return buttons::b_part;
                }

				return buttons::none;
			}

            bool drawer::update_value(buttons _what, const nana::point& _pos)
            {
                const value_type old = metrics_.value;
                if (_what == buttons::rg_part)
                {
                    metrics_.value.r(get_r(_pos.x));
                    metrics_.value.g(get_g(_pos.y));
                }
                else if (_what == buttons::b_part)
                {
                    metrics_.value.b(get_b(_pos.x));
                }
                return old != metrics_.value;
            }

			void drawer::draw(graph_reference graph, buttons what)
			{
				_m_background(graph);

                _m_draw_color(graph, buttons::rg_part);
                _m_draw_color(graph, buttons::b_part);
                _m_draw_color(graph, buttons::sample_part);

                _m_draw_cursor(graph, buttons::rg_part);
                _m_draw_cursor(graph, buttons::b_part);

            }
		//private:
			void drawer::_m_background(graph_reference graph)
			{
				graph.rectangle(true, {0xd0, 0xd0, 0xd0});
			}
 
            void drawer::_m_draw_color(graph_reference graph, buttons what)
            { 
                if (what == buttons::rg_part)
                {
                    for (int r = rg_left; r < rg_right; ++r)
                    {
                        for (int g = rg_top; g < rg_bottom; ++g)
                        {
                            color_rgb rgb{ get_r(r), get_g(g), metrics_.value.b() };
                            graph.set_pixel(r, g, rgb.to_color());
                        }
                    }
                }
                else if (what == buttons::b_part)
                {
                    for (int b = b_left; b < b_right; ++b)
                    {
                        color_rgb rgb{ metrics_.value.r(), metrics_.value.g(), get_b(b) };
                        graph.line({ b, b_top }, { b, b_bottom }, rgb.to_color());
                    }
                }
                else if (what == buttons::sample_part)
                {
                    graph.rectangle({ sample_left, sample_top, sample_width, sample_height }, true, metrics_.value);
                }
            }

            nana::color get_cursor_color(color_rgb value)
            {
                return value.b() < 128 ? nana::colors::white : nana::colors::black;
            }

            void drawer::_m_draw_cursor(graph_reference graph, buttons what)
            {
                if (what == buttons::rg_part)
                {
                    nana::rectangle r{ get_x_by_r(metrics_.value.r()) - 5, get_y_by_g(metrics_.value.g()) - 5, 10, 10 };
                    graph.round_rectangle(r, 5, 5, get_cursor_color(metrics_.value), false, {});
                }
                else if (what == buttons::b_part)
                {
                    nana::rectangle r{ get_x_by_b(metrics_.value.b()) - 5, b_top - 5, 10, 10 + b_height };
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
                        value.r() += 255 * (_multiple) / drawer::rg_width;
                        if (value.r() > 255)
                            value.r() = 255;
                    }
                    else if (arg.shift)
                    {
                        value.g() += 255 * (_multiple) / drawer::rg_height;
                        if (value.g() > 255)
                            value.g() = 255;
                    }
                    else
                    {
                        value.b() += 255 * (_multiple) / drawer::b_width;
                        if (value.b() > 255)
                            value.b() = 255;
                    }
                }
                else
                {
                    if (arg.ctrl)
                    {
                        uint step = 255 * (_multiple) / drawer::rg_width;
                        if (value.r() > step)
                            value.r() -= step;
                        else
                            value.r() = 0;
                    }
                    else if (arg.shift)
                    {
                        uint step = 255 * (_multiple) / drawer::rg_height;
                        if (value.g() > step)
                            value.g() -= step;
                        else
                            value.g() = 0;
                    }
                    else
                    {
                        uint step = 255 * (_multiple) / drawer::b_width;
                        if (value.b() > step)
                            value.b() -= step;
                        else
                            value.b() = 0;
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
                widget_ = dynamic_cast<runa::color_rgb_chooser*>(&widget);
                widget.caption("runa_color_rgb_chooser");
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
	
        }//end namespace color_rgb_chooser

    }//end namespace drawerbase

}//end namespace runa

#endif

