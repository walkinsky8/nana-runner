// Created by walkinsky(lyh6188@hotmail.com), 2018/10/02
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/widget_base.h>

nana::color nana::runner::get_color(const string& _s)
{
	try {
		nana::colors* clr = colors::find_value(_s);
		if (clr)
			return nana::color{ *clr };
		return nana::color{ _s };
	}
	catch (std::exception& e) {
		NAR_LOG("exception: " << e.what() << ": " << _s);
	}
	return nana::colors::black;
}

nana::runner::font nana::runner::make_font(const string& _name, double _size, bool _bold, bool _italic, bool _underline, bool _strikeout)
{
	return font{ _name, _size, font::font_style{ _bold ? 700u : 400u, _italic, _underline, _strikeout } };
}

nana::runner::dumper& nana::runner::operator<<(dumper& _d, const point& _v)
{
	bool old = _d.compact(true);
	std::vector<int> values;
	values.push_back(_v.x);
	values.push_back(_v.y);
	_d << values;
	_d.compact(old);
	return _d;
}

void nana::runner::operator >> (const parser& _p, point& _v)
{
	std::vector<int> values;
	_p >> values;
	if (values.size() > 0)
		_v.x = values[0];
	if (values.size() > 1)
		_v.y = values[1];
}

nana::runner::dumper& nana::runner::operator<<(dumper& _d, const size& _v)
{
	bool old = _d.compact(true);
	std::vector<unsigned> values;
	values.push_back(_v.width);
	values.push_back(_v.height);
	_d << values;
	_d.compact(old);
	return _d;
}

void nana::runner::operator >> (const parser& _p, size& _v)
{
	std::vector<nana::size::value_type> values;
	_p >> values;
	if (values.size() > 0)
		_v.width = values[0];
	if (values.size() > 1)
		_v.height = values[1];
}

nana::runner::dumper& nana::runner::operator<<(dumper& _d, const font& _v)
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

void nana::runner::operator >> (const parser& _p, font& _v)
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

void nana::runner::operator << (string& _w, const color& _v)
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
		_w << "," << g;
		_w << "," << b;
		_w << ")";
	}
}

void nana::runner::operator >> (const string& _s, color& _v)
{
	_v = get_color(_s);
}

#endif

