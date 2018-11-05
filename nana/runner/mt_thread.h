// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <thread>
#include <nana/runner/mt_monitor.h>
#include <nana/runner/mt_mutex.h>

namespace nana::runner {

    class simple_thread
    {
        std::shared_ptr<std::thread> thr_;

        mt::monitor<mt::mutex> mon_;

        volatile bool running_{ true };
        volatile bool paused_{ false };

    public:
        virtual ~simple_thread() = default;

        void open();

        void close();

        void stop_running();
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
        virtual void on_loop() { }
        virtual void on_death() { }

        // called by close()
        virtual void on_close() { }

    };

}
