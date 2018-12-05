// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <runa/foundation/app_base.h>

#include <runa/editor/login_cntrl.h>
#include <runa/editor/editor_cntrl.h>

namespace runa::editor {

    class editor_app : public app
    {
        login_cntrl login_;
        editor_cntrl editor_;

    public:
        editor_app();

    protected:
        void on_init() override;

        void on_fini() override;

    };

}

