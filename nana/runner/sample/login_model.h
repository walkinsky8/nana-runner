// Created by walkinsky(lyh6188@hotmail.com), 2018/02/20
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/model_base.h>

namespace nana::runner::sample::model {

    class login : public model_obj
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

}
