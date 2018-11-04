// Created by walkinsky(lyh6188@hotmail.com), 2018/11/04
#pragma once

#include <nana/runner/base_config.h>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace nana::runner {

    class simple_thread
    {
        std::shared_ptr<std::thread> thr_;

        volatile bool running_{ true };

    public:
        virtual ~simple_thread() = default;

        void open();

        void close();

        void stop_running();

        bool running() const { return running_; }

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
