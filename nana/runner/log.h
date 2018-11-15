// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/base_types.h>

#include <nana/runner/util.h>

#include <nana/runner/mt_thread.h>
#include <nana/runner/mt_queue.h>

#define NAR_LOG(x)         NAR_LOG_INFO(x)

#define NAR_LOG_VAR(x)     NAR_LOG_NV(#x, x)
#define NAR_LOG_NV(n, v)   NAR_LOG_DEBUG(n << " = " << v)

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

    class out
    {
        std::ostringstream oss_;

    public:
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

    struct log_head
    {
        datetime dt_;
        log_level ll_;
        pcstr file_;
        int line_;
        pcstr func_;

        log_head() = default;
        log_head(log_level _ll, pcstr _file, int _line, pcstr _func);

    };

    class log
    {
        log_head head_;
        std::ostringstream buf_;
        
    public:
        log(log_level _ll, pcstr _file, int _line, pcstr _func);
        ~log();

        template<class T>
        inline log& operator<<(const T& _v)
        {
            buf_ << _v;
            return *this;
        }

        inline log& operator<<(std::ostream& (__cdecl *_Pfn)(std::ostream&))
        {
            buf_ << _Pfn;
            return *this;
        }

    };

    class log_record
    {
        log_head head_;
        string buf_;

    public:
        log_record() = default;
        log_record(log_head && _head, string && _buf);

        string str() const;

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const log_record& _v)
    {
        return _v.dump(_os);
    }

    class log_thread : public simple_thread
    {
        typedef mt::queue<log_record> _Q;
        _Q records_;

    public:
        static log_thread& instance();

    public:
        log_thread();

        void put(log_record&& _record);

    protected:
        void on_birth() override;
        void on_death() override;
        void on_loop() override;
        void on_stop() override;

    };

}

