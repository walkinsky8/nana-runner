/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2019/03/09
#pragma once

#include <runa/widgets/widget_all.h>

#include <runa/foundation/app_base.h>

namespace runa {

    template<class _Widget, class _Data>
    void on_text_changed(_Widget const* _widget, _Data* _data, callback _fn)
    {
        _widget->events().text_changed([=] { *_widget >> *_data; _fn(); });
    }

    template<class _Widget, class _Data>
    void on_selected(_Widget const* _widget, _Data* _data, callback _fn)
    {
        _widget->events().selected([=] { *_widget >> *_data; _fn(); });
    }

    template<class _Widget, class _Data>
    void on_focus(_Widget const* _widget, _Data* _data, callback _fn)
    {
        _widget->events().focus([=] { *_widget >> *_data; _fn(); });
    }

    template<class _Widget, class _Data>
    void on_value_changed(_Widget const* _widget, _Data* _data, callback _fn)
    {
        _widget->events().value_changed([=] { *_widget >> *_data; _fn(); });
    }

    template<class _Widget, class _Data>
    void on_checked(_Widget const* _widget, _Data* _data, callback _fn)
    {
        _widget->events().checked([=] { *_widget >> *_data; _fn(); });
    }

}
