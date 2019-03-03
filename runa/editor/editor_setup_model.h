/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/11/09
#pragma once

#include <runa/foundation/model_base.h>

#include <runa/foundation/font/font_model.h>
#include <runa/foundation/color/color_model.h>

namespace runa::editor {

        class editor_setup_model : public model_obj, public model_proxy_base<editor_setup_model>
        {
            NAR_DEFINE_MODEL(editor_setup, model_obj);

            class colors_model : public model_obj
            {
                NAR_DEFINE_MODEL(colors, model_obj);

                NAR_FIELD(color_model, bg);
                NAR_FIELD(color_model, fg);

            public:
                template<class _Stream>
                void traverse(_Stream& _s)
                {
                    super::traverse(_s);
                    NAR_CODEC(_s, bg);
                    NAR_CODEC(_s, fg);
                }
            };

            NAR_FIELD(font_model, font);
            NAR_FIELD(colors_model, colors);
            NAR_FIELD(string, caption);

        public:
            template<class _Stream>
            void traverse(_Stream& _s)
            {
                super::traverse(_s);
                NAR_CODEC(_s, font);
                NAR_CODEC(_s, colors);
                NAR_CODEC(_s, caption);
            }

        };

}

