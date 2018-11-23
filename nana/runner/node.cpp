// Created by walkinsky(lyh6188@hotmail.com), 2017/11/1
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/node.h>

#include <nana/runner/dumper.h>

void runa::node::clear()
{
    name_.clear();
    type_.clear();
    value_.clear();
    children_.clear();
}

void runa::node::traverse(dumper& _d)
{
    for (auto& i : children_.list())
    {
        if (i.simple())
            _d(i.name(), i.value());
        else
            _d(i.name(), i.children().list());
    }
}

#endif

