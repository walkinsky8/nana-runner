// Created by walkinsky(lyh6188@hotmail.com), 2018/11/17
#pragma once

#include <runa/foundation/controller_base.h>

namespace runa::sample {

    class demo_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(demo_cntrl, controller_obj);

		view_ptr demo_;
        view_ptr hello_;
        view_ptr color_;
        view_ptr font_;
        view_ptr dummy_;
        view_ptr generic_;

    public:
        demo_cntrl();

        void open(callback _on_complete);

        void close();

    };

}

