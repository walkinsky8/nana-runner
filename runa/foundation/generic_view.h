// Created by walkinsky(lyh6188@hotmail.com), 2018/10/12
#pragma once

#include <runa/foundation/view_base.h>

#include <runa/widgets/form_cfg.h>

namespace runa {

    class generic_view : public view_obj
    {
        NAR_DEFINE_VIEW(generic, view_obj);

    public:
        generic_view(widget_cfg& _cfg, window _parent)
            : super{ _cfg, _parent }
        {
        }

    private:

    };

}
