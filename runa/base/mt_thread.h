/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created on 2018/11/04
#pragma once

#include <runa/base/_config.h>

#include <thread>
#include <runa/base/mt_monitor.h>
#include <runa/base/mt_mutex.h>

namespace runa {

    using thread_ptr = std::shared_ptr<std::thread>;

    class simple_thread
    {
        thread_ptr thr_;

        mt::monitor<mt::mutex> mon_;

        volatile bool running_{ false };
        volatile bool paused_{ false };

    public:
        virtual ~simple_thread() = default;

        void start();

        void stop();

        void running(bool _running);
        bool running() const;

        void pause();
        void resume();
        bool paused() const;

        void wakeup();
        void wait();
        void wait(unsigned _milliseconds);

        static void sleep(unsigned _milliseconds);

    protected:
        virtual void run();

        // called by run()
        virtual void on_birth() { }
        virtual void on_death() { }
        virtual void on_loop() { }

        // called by stop()
        virtual void on_stop() { }

    };

}
