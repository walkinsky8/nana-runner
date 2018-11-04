// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <nana/runner/base_types.h>

#include <concurrent_queue.h>

namespace nana::runner::mt {

    template<class T>
    using queue = concurrency::concurrent_queue<T>;

}
