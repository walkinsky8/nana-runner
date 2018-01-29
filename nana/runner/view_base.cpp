// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/view_base.h>

#include <nana/runner/widget_cfg.h>

nana::runner::view_obj::view_obj(widget_cfg& _cfg)
    : cfg_{ _cfg }
{
}

void nana::runner::view_obj::show(bool _visible)
{
    cfg_.show(_visible);
}

void nana::runner::view_obj::close()
{
    cfg_.close();
}
