// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>
#include <nana/runner/log.h>
#include <nana/runner/dumper.h>
#include <nana/runner/parser.h>

#include <nana/gui.hpp>

#include <nana/filesystem/filesystem.hpp>
#include <nana/filesystem/filesystem_ext.hpp>

namespace nana::runner {

    using point = nana::point;
    using size = nana::size;
    using font = nana::paint::font;
    using color = nana::color;
    using colors = enum_<nana::colors, nana::colors::black>;
    using cursor = enum_<nana::cursor, nana::cursor::arrow>;
    using align = enum_<nana::align, nana::align::left>;
    using align_v = enum_<nana::align_v, nana::align_v::top>;

    namespace fs = std::experimental::filesystem;
    namespace fs_ext = nana::filesystem_ext;

    class widget_cfg;

    class view_obj : public object
    {
        widget_cfg& cfg_;

    public:
        view_obj(widget_cfg& _cfg);

        widget_cfg& cfg()
        {
            return cfg_;
        }

        void show(bool _visible = true);

        void close();

        void close_all();

    };

}
