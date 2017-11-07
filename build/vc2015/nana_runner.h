// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

namespace nana::runner
{
    class app
    {
        wstring cmdline_;

    public:
        app(const wchar_t* _cmdline);

        int go();

    private:
        void show();

    };

}