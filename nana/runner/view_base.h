// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/base_types.h>
#include <nana/runner/log.h>
#include <nana/runner/dumper.h>
#include <nana/runner/parser.h>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>

namespace nana::runner {

    color get_color(const string& _s);

    template<class T>
    struct new_
    {
        using new_func = std::function<T* (string const&)>;

        new_func operator()() const
        {
            return [](string const&) {
                return new T();
            };
        }

    };

}
