// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>
#include <nana/runner/log.h>
#include <nana/runner/dumper.h>
#include <nana/runner/parser.h>

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/categorize.hpp>

#include <nana/filesystem/filesystem.hpp>
#include <nana/filesystem/filesystem_ext.hpp>

namespace nana::runner {

    namespace fs = std::experimental::filesystem;
    namespace fs_ext = nana::filesystem_ext;

    using point = nana::point;
    using size = nana::size;
    using font = nana::paint::font;
    using cursor = enum_<nana::cursor, nana::cursor::arrow>;
    using align = enum_<nana::align, nana::align::left>;
    using align_v = enum_<nana::align_v, nana::align_v::top>;

    using nana::textbox;
    using categorize = nana::categorize<std::string>;

    color get_color(const string& _s);

    font make_font(const string& _name, double _size, bool _bold, bool _italic, bool _strikeout, bool _underline);

    dumper& operator<<(dumper& _d, const point& _v);
    void operator >> (const parser& _p, point& _v);

    dumper& operator<<(dumper& _d, const size& _v);
    void operator >> (const parser& _p, size& _v);

    dumper& operator<<(dumper& _d, const font& _v);
    void operator >> (const parser& _p, font& _v);

    template<class T>
    textbox& operator<<(textbox& _w, const T& _v)
    {
        string s = _w.caption();
        s << _v;
        _w.caption(s);
        return _w;
    }

    template<class T>
    void operator>>(const textbox& _w, T& _v)
    {
        string s = _w.caption();
        s >> _v;
    }

    string& operator << (string& _w, const color& _v);
    void operator >> (const string& _w, color& _v);

}
