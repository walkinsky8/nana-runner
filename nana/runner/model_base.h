// Created by walkinsky(lyh6188@hotmail.com), 2018/01/21
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/view_base.h>

namespace nana::runner {

    color get_color(const string& _s);

    font make_font(const string& _name, double _size, bool _bold, bool _italic, bool _underline, bool _strikeout);

    dumper& operator<<(dumper& _d, const point& _v);
    void operator >> (const parser& _p, point& _v);

    dumper& operator<<(dumper& _d, const size& _v);
    void operator >> (const parser& _p, size& _v);

    dumper& operator<<(dumper& _d, const font& _v);
    void operator >> (const parser& _p, font& _v);

    string& operator << (string& _w, const color& _v);
    void operator >> (const string& _w, color& _v);

    class model_object : public object
    {

    };

}
