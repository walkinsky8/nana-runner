// Created by walkinsky(lyh6188@hotmail.com), 2018/12/03
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "color_rgb.h"

namespace runa
{
    std::ostream& operator<<(std::ostream& _os, const color_rgb& _v)
    {
        _os << "rgb(" << _v.r();
        _os << ", " << _v.g();
        _os << ", " << _v.b();
        _os << ")";
        return _os;
    }
    
    void operator>>(string& _is, color_rgb& _v)
    {
        nana::color c{ _is };
        _v = c;
    }

}//end namespace runa

#endif

