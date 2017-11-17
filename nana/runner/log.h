// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#define NAR_LOG(x) log() << x
#define NAR_LOG_NV(n, v) NAR_LOG(n << " = " << v)
#define NAR_LOG_VAR(x) NAR_LOG_NV(#x, x)

namespace nana::runner {

    using log_handler = std::function<void(const string&)>;
    log_handler get_log_handler();
    log_handler set_log_handler(log_handler);

    void write_console(const string& _msg);

    struct out
    {
        std::ostringstream oss_;

        ~out();

        std::string str() const
        {
            return oss_.str();
        }

        template<class T>
        inline out& operator<<(const T& _v)
        {
            oss_ << _v;
            return *this;
        }

        inline out& operator<<(std::ostream& (__cdecl *_Pfn)(std::ostream&))
        {
            oss_ << _Pfn;
            return *this;
        }

    };

    struct log
    {
        out oss_;
        
        log();
        ~log();

        std::string str() const
        {
            return oss_.str();
        }

        template<class T>
        inline log& operator<<(const T& _v)
        {
            oss_ << _v;
            return *this;
        }

        inline log& operator<<(std::ostream& (__cdecl *_Pfn)(std::ostream&))
        {
            oss_ << _Pfn;
            return *this;
        }

    };

}
