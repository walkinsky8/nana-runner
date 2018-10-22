// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base_config.h>

#include <nana/runner/base_types.h>

#define NAR_LOG_VAR(x)     NAR_LOG_NV(#x, x)
#define NAR_LOG_NV(n, v)   NAR_LOG_DEBUG(n << " = " << v)
#define NAR_LOG(x)         NAR_LOG_INFO(x)

#define NAR_LOG_ERROR(x)   NAR_LOG_(nana::runner::LL_ERROR, x)
#define NAR_LOG_WARN(x)    NAR_LOG_(nana::runner::LL_WARN, x)
#define NAR_LOG_INFO(x)    NAR_LOG_(nana::runner::LL_INFO, x)
#define NAR_LOG_DEBUG(x)   NAR_LOG_(nana::runner::LL_DEBUG, x)
#define NAR_LOG_VERBOSE(x) NAR_LOG_(nana::runner::LL_VERBOSE, x)

#define NAR_LOG_(ll, x)    nana::runner::log(ll, __FILE__, __LINE__, __FUNCTION__) << x

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

    enum log_level
    {
        LL_ERROR,
        LL_WARN,
        LL_INFO,
        LL_DEBUG,
        LL_VERBOSE,
        LL_UNKNOWN = -1
    };
    using enum_log_level = enum_<log_level, LL_UNKNOWN>;

    struct log
    {
        out oss_;
        
        log(log_level _ll, pcstr _file, int _line, pcstr _func);
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
