// Created by walkinsky(lyh6188@hotmail.com), 2017/11/1
#include "stdafx.h"

#include <nana/runner/node.h>

#include <nana/runner/dumper.h>

void nana::runner::node::traverse(dumper& _d)
{
    for (auto& i : children_.list())
    {
        if (i.simple())
            _d(i.name(), i.value());
        else
            _d(i.name(), i.children().list());
    }
}
