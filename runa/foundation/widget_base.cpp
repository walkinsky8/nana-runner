/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/02
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/foundation/widget_base.h>

#include <runa/foundation/color/color_rgb.h>
#include <runa/foundation/color/color_hsl.h>
#include <runa/foundation/color/color_hsv.h>

nana::color runa::get_color(const string& _s, color _default)
{
	try {
        if (_s.empty())
            return _default;
		nana::colors* clr = colors::find_value(_s);
		if (clr)
			return nana::color{ *clr };
		return parse_color(_s);
	}
	catch (std::exception& e) {
        NAR_LOG_EXCPT(e << ": " << _s);
	}
	return _default;
}

void runa::throw_invalid_color(istr _msg)
{
    const static string excpt_what = "color: invalid color format: ";
    throw std::invalid_argument(istr(excpt_what) + _msg);
}

std::string runa::read_number(std::string& str, std::size_t& pos)
{
    pos = str.find_first_of("0123456789", pos);
    if (pos == str.npos)
        return{};

    auto end = str.find_first_not_of("0123456789", pos + 1);
    //integer part
    if (end == str.npos)
    {
        pos = end;
        return str.substr(pos);
    }

    if (str[end] == '.')
    {
        auto decimal_end = str.find_first_not_of("0123456789", end + 1);
        if ((decimal_end == str.npos) || (decimal_end == end + 1)) //Because of missing %
            return{};

        end = decimal_end;
    }

    auto ch = str[end];
    if (ch == '%' || ch == ' ' || ch == ',' || ch == ')')
    {
        auto start = pos;
        pos = end + (ch == '%' ? 1 : 0);
        return str.substr(start, pos - start);
    }
    return{};
}

runa::color runa::parse_color(const string& _s)
{
    string css_color = _s;

    auto pos = css_color.find_first_not_of(' ');
    if (pos == css_color.npos)
        throw_invalid_color("empty");

    if ('#' == css_color[pos])
    {
        if (css_color.size() < pos + 4)
            throw_invalid_color("#rgb less than 4 characters");

        auto endpos = css_color.find_first_not_of("0123456789abcdefABCDEF", pos + 1);
        if (endpos == css_color.npos)
            endpos = static_cast<decltype(endpos)>(css_color.size());

        if ((endpos - pos != 4) && (endpos - pos != 7))
            throw_invalid_color("neither #rgb nor #rrggbb");

        auto n = std::stoi(css_color.substr(pos + 1, endpos - pos - 1), nullptr, 16);

        uint r, g, b;
        if (endpos - pos == 4)
        {
            r = ((0xF00 & n) >> 4) | ((0xF00 & n) >> 8);
            g = (0xF0 & n) | ((0xF0 & n) >> 4);
            b = (0xF & n) | ((0xF & n) << 4);
        }
        else
        {
            r = (0xFF0000 & n) >> 16;
            g = (0xFF00 & n) >> 8;
            b = (0xFF & n);
        }

        return color{ r, g, b };
    }

    //std::tolower is not allowed because of concept requirements
    string_tolower(css_color);
    auto endpos = css_color.find(' ', pos + 1);
    if (endpos == css_color.npos)
        endpos = css_color.size();

    color result{};

    if ((endpos - pos == 11) && (css_color.substr(pos, 11) == "transparent"))
    {
        return result;
    }

    auto type_end = css_color.find_first_of(" (", pos + 1);

    if (type_end == css_color.npos || ((type_end - pos != 3) && (type_end - pos != 4)))	//rgb/hsl = 3, rgba/hsla = 4
        throw_invalid_color("neither rgb/hsl/hsv() nor rgba/hsla/hsva()");

    bool has_alpha = false;
    if (type_end - pos == 4) //maybe rgba/hsla
    {
        if (css_color[pos + 3] != 'a')
            throw_invalid_color("the 4th char not 'a'");
        has_alpha = true;
    }

    auto type_name = css_color.substr(pos, 3);
    pos = css_color.find_first_not_of(' ', type_end);
    if (pos == css_color.npos || css_color[pos] != '(')
        throw_invalid_color("no '(' after rgb/hsl/hsv[a]");

    auto str = read_number(css_color, ++pos);
    if (str.empty())
        throw_invalid_color("no digits in ()");

    if ("rgb" == type_name)
    {
        std::vector<std::string> rgb;

        rgb.emplace_back(std::move(str));
        const bool is_real = (rgb.back().back() == '%');

        for (int i = 0; i < 2; ++i)
        {
            pos = css_color.find_first_not_of(' ', pos);
            if (pos == css_color.npos || css_color[pos] != ',')
                throw_invalid_color("no ',' in rgb()");

            str = read_number(css_color, ++pos);
            if (str.empty())
                throw_invalid_color("empty after ',' in rgb()");

            rgb.emplace_back(std::move(str));
            if (rgb.size() == 3)
                break;
        }

        if (rgb.size() != 3)
            throw_invalid_color("no 3 elements in rgb()");

        double r, g, b;
        if (is_real)
        {
            auto pr = std::stod(rgb[0].substr(0, rgb[0].size() - 1));
            r = (pr > 100 ? 255.0 : 2.55 * pr);

            pr = std::stod(rgb[1].substr(0, rgb[1].size() - 1));
            g = (pr > 100 ? 255.0 : 2.55 * pr);

            pr = std::stod(rgb[2].substr(0, rgb[2].size() - 1));
            b = (pr > 100 ? 255.0 : 2.55 * pr);
        }
        else
        {
            r = std::stod(rgb[0]);
            if (r > 255.0)	r = 255;

            g = std::stod(rgb[1]);
            if (g > 255.0)	g = 255;

            b = std::stod(rgb[2]);
            if (b > 255.0)	b = 255;
        }
        result = (color)color_rgb { r, g, b };
    }
    else if ("hsl" == type_name)
    {
        if (str.back() == '%')
            throw_invalid_color("unexpected h part '%' in hsl()");

        auto h = std::stod(str);

        pos = css_color.find_first_not_of(' ', pos);
        if (pos == css_color.npos || css_color[pos] != ',')
            throw_invalid_color("no ',' after h part in hsl()");

        str = read_number(css_color, ++pos);
        if (str.empty() || str.back() != '%')
            throw_invalid_color("miss s part '%' in hsl()");

        auto s = std::stod(str.substr(0, str.size() - 1));

        pos = css_color.find_first_not_of(' ', pos);
        if (pos == css_color.npos || css_color[pos] != ',')
            throw_invalid_color("no ',' after s part in hsl()");

        str = read_number(css_color, ++pos);
        if (str.empty() || str.back() != '%')
            throw_invalid_color("miss l part '%' in hsl()");

        auto l = std::stod(str.substr(0, str.size() - 1));

        h = runa::ensure_between(h, 0.0, 360.0);
        s = runa::ensure_between(s, 0.0, 100.0);
        l = runa::ensure_between(l, 0.0, 100.0);
        result = (color)color_hsl { h, s / 100, l / 100 };
    }
    else if ("hsv" == type_name)
    {
        if (str.back() == '%')
            throw_invalid_color("unexpected '%' in h part in hsl()");
        
        auto h = std::stod(str);

        pos = css_color.find_first_not_of(' ', pos);
        if (pos == css_color.npos || css_color[pos] != ',')
            throw_invalid_color("no ',' after h part in hsv()");

        str = read_number(css_color, ++pos);
        if (str.empty() || str.back() != '%')
            throw_invalid_color("miss s part '%' in hsv()");

        auto s = std::stod(str.substr(0, str.size() - 1));

        pos = css_color.find_first_not_of(' ', pos);
        if (pos == css_color.npos || css_color[pos] != ',')
            throw_invalid_color("no ',' after s part in hsv()");

        str = read_number(css_color, ++pos);
        if (str.empty() || str.back() != '%')
            throw_invalid_color("miss v part '%' in hsv()");

        auto v = std::stod(str.substr(0, str.size() - 1));

        h = runa::ensure_between(h, 0.0, 360.0);
        s = runa::ensure_between(s, 0.0, 100.0);
        v = runa::ensure_between(v, 0.0, 100.0);
        result = (color)color_hsv { h, s / 100, v / 100 };
    }
    else
        throw_invalid_color("invalid color type");

    if (has_alpha)
    {
        str = read_number(css_color, ++pos);
        if (str.empty() || str.back() == '%')
            throw_invalid_color("empty or unexpected '%' in alpha part");

        result = result.alpha(std::stod(str));
    }

    return result;
}

runa::font runa::make_font(const string& _name, double _size, bool _bold, bool _italic, bool _underline, bool _strikeout)
{
	return font{ _name, _size, font::font_style{ _bold ? 700u : 400u, _italic, _underline, _strikeout } };
}

runa::dumper& runa::operator<<(dumper& _d, const point& _v)
{
	bool old = _d.compact(true);
	std::vector<int> values;
	values.push_back(_v.x);
	values.push_back(_v.y);
	_d << values;
	_d.compact(old);
	return _d;
}

void runa::operator >> (const parser& _p, point& _v)
{
	std::vector<int> values;
	_p >> values;
	if (values.size() > 0)
		_v.x = values[0];
	if (values.size() > 1)
		_v.y = values[1];
}

runa::dumper& runa::operator<<(dumper& _d, const size& _v)
{
	bool old = _d.compact(true);
	std::vector<unsigned> values;
	values.push_back(_v.width);
	values.push_back(_v.height);
	_d << values;
	_d.compact(old);
	return _d;
}

void runa::operator >> (const parser& _p, size& _v)
{
	std::vector<nana::size::value_type> values;
	_p >> values;
	if (values.size() > 0)
		_v.width = values[0];
	if (values.size() > 1)
		_v.height = values[1];
}

runa::dumper& runa::operator<<(dumper& _d, const font& _v)
{
	bool old = _d.compact(true);
	_d.enter({});
	_d.indent().write(_v.name());
	_d.indent().write(_v.size());
	if (_v.bold())
		_d.indent().write("bold");
	if (_v.italic())
		_d.indent().write("italic");
	if (_v.strikeout())
		_d.indent().write("strikeout");
	if (_v.underline())
		_d.indent().write("underline");
	_d.leave();
	_d.compact(old);
	return _d;
}

void runa::operator >> (const parser& _p, font& _v)
{
	if (!_p.valueIsEmpty())
	{
		string name;
		double size = _v.size();
		bool bold = _v.bold();
		bool italic = _v.italic();
		bool strikeout = _v.strikeout();
		bool underline = _v.underline();
		for (auto& i : _p.unit().children().list())
		{
			const auto& v = i.value();
			if (v.empty())
				continue;
			if (v == "bold")
				bold = true;
			else if (v == "italic")
				italic = true;
			else if (v == "strikeout")
				strikeout = true;
			else if (v == "underline")
				underline = true;
			else if (is_digit(v[0]))
				v >> size;
			else
			{
				if (!name.empty())
					name += ' ';
				name += v;
			}
		}
		if (name.empty())
			name = _v.name();
		_v = make_font(name, size, bold, italic, underline, strikeout);
	}
}

void runa::operator << (string& _w, const color& _v)
{
    _w.clear();
	unsigned r = (unsigned)(_v.r() + 0.5);
	unsigned g = (unsigned)(_v.g() + 0.5);
	unsigned b = (unsigned)(_v.b() + 0.5);
	unsigned c = (r << 16) + (g << 8) + b;
	string* s = colors::find_name(c);
	if (s)
		_w << *s;
	else
	{
		_w << "rgb(";
		_w << r;
		_w << ", " << g;
		_w << ", " << b;
		_w << ")";
	}
}

void runa::operator >> (const string& _s, color& _v)
{
	_v = get_color(_s, _v);
}

runa::dumper& runa::operator<<(dumper& _d, const nana::color& _v)
{
    string s;
    s << _v;
    return _d.write(s);
}

runa::dumper& runa::operator<<(dumper& _d, const nana::arg_click& _v)
{
    _d.enter("arg_click");
    _d("mouse=", *_v.mouse_args);
    _d.leave();
    return _d;
}

runa::dumper& runa::operator<<(dumper& _d, const nana::arg_mouse& _v)
{
    _d.enter("arg_mouse");
    _d("evt_code", runa::event_code{ _v.evt_code });
    _d("pos", _v.pos);
    _d("button", runa::mouse{ _v.button });
    _d("left_button", _v.left_button);
    _d("mid_button", _v.mid_button);
    _d("right_button", _v.right_button);
    _d("alt", _v.alt);
    _d("shift", _v.shift);
    _d("ctrl", _v.ctrl);
    _d("is_left_button", _v.is_left_button());
    _d.leave();
    return _d;
}

runa::dumper& runa::operator<<(dumper& _d, const nana::arg_wheel& _v)
{
    _d.enter("arg_wheel");
    _d("mouse=", (const nana::arg_mouse&)_v);
    _d("which", runa::wheel{ _v.which });
    _d("upwards", _v.upwards);
    _d("distance", _v.distance);
    _d.leave();
    return _d;
}

#endif

