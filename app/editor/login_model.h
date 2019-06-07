/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/02/20
#pragma once

#include <runa/foundation/model_base.h>

namespace runa { namespace editor {

    class login_model : public model_obj, public model_proxy_base<login_model>
    {
        NAR_DEFINE_MODEL(login, model_obj);

    public:
        NAR_FIELD(string, username);
        NAR_FIELD(string, password);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, username);
            NAR_CODEC(_s, password);
        }

    };

}}

