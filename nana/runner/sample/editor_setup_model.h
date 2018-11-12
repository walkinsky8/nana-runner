// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#pragma once

#include <nana/runner/model_base.h>

#include <nana/runner/model_font.h>
#include <nana/runner/model_color.h>

namespace nana::runner::sample {

        class editor_setup_model : public model_obj
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

        public:
            template<class _Stream>
            void traverse(_Stream& _s)
            {
                super::traverse(_s);
                NAR_CODEC(_s, font);
                NAR_CODEC(_s, colors);
            }

        };

}

