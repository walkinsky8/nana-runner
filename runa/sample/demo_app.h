// Created by walkinsky(lyh6188@hotmail.com), 2018/11/15
#pragma once

#include <runa/foundation/app_base.h>

#include <runa/sample/demo_cntrl.h>

namespace runa::sample {

    class demo_app : public app
    {
        demo_cntrl demo_;

    public:
        demo_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}

