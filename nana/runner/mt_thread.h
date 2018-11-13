// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/_config.h>

#include <thread>
#include <nana/runner/mt_monitor.h>
#include <nana/runner/mt_mutex.h>

namespace nana::runner {

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
