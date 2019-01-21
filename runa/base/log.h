/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2017/01/15
#pragma once

#include <runa/base/_config.h>

#include <runa/base/base_types.h>

#include <runa/base/util.h>

#include <runa/base/mt_thread.h>
#include <runa/base/mt_queue.h>
#include <runa/base/mt_vector.h>

#define NAR_LOG(x)          NAR_LOG_INFO(x)

#define NAR_LOG_VAR(x)      NAR_LOG_NV(#x, x)
#define NAR_LOG_NV(n, v)    NAR_LOG_DEBUG(n << " = " << v)

#define NAR_LOG_EXCPT(x)    NAR_LOG_(runa::LL_EXCEPTION, false, x)
#define NAR_LOG_ERROR(x)    NAR_LOG_(runa::LL_ERROR, false, x)
#define NAR_LOG_WARN(x)     NAR_LOG_(runa::LL_WARN, false, x)
#define NAR_LOG_INFO(x)     NAR_LOG_(runa::LL_INFO, false, x)
#define NAR_LOG_DEBUG(x)    NAR_LOG_(runa::LL_DEBUG, false, x)
#define NAR_LOG_VERBOSE(x)  NAR_LOG_(runa::LL_VERBOSE, false, x)
#define NAR_OUT(x)          NAR_LOG_(runa::LL_OUTPUT, true, x)

#define NAR_LOG_(ll, oo, x) runa::log(ll, oo, NAR_CURRENT()) << x

#define NAR_CURRENT()       runa::current_info{__FILE__, __LINE__, __FUNCTION__}

#define NAR_THROW_ERROR(e, x)  throw e{(runa::out()<<NAR_CURRENT()<<" "<<#e<<": "<<x).str().c_str()}

namespace runa {

    struct current_info
    {
        pcstr file_{};
        int line_{};
        pcstr func_{};

        current_info()
        {}
        current_info(pcstr _file, int _line, pcstr _func)
            :file_{ _file }, line_{ _line }, func_{ _func }
        {}

        string str() const
        {
            return to_str(*this);
        }

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const current_info& _v)
    {
        return _v.dump(_os);
    }

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
        LL_EXCEPTION,
        LL_ERROR,
        LL_WARN,
        LL_INFO,
        LL_DEBUG,
        LL_VERBOSE,
        LL_OUTPUT,
        LL_UNKNOWN = -1
    };
    using enum_log_level = enum_<log_level, LL_UNKNOWN>;

    struct log_head
    {
        datetime dt_;
        enum_log_level ll_;
        bool out_only_{ false };
        current_info current_;

        log_head();
        log_head(log_level _ll, bool _out_only, current_info const& _current);

        string str() const
        {
            return to_str(*this);
        }

        std::ostream& dump(std::ostream& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const log_head& _v)
    {
        return _v.dump(_os);
    }

    class log
    {
        log_head head_;
        std::ostringstream buf_;

    public:
        log(log_level _ll, bool _out_only, current_info const& _current);
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

        const log_head& head() const
        {
            return head_;
        }

        const string& buf() const
        {
            return buf_;
        }

        string str() const
        {
            return to_str(*this);
        }

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
        volatile bool output_derectly_{ false };

    public:
        static log_thread& instance();

    public:
        log_thread();

        void put(log_record&& _record);

        void output_derectly(bool _v);

    protected:
        void on_birth() override;
        void on_death() override;
        void on_loop() override;
        void on_stop() override;

    };

    class log_handler
    {
    public:
        using func = std::function<void(const string&)>;
        using func_ptr = std::shared_ptr<optional<func>>;

    private:
        mt::vector<func_ptr> funcs_;

    public:
        static log_handler& instance();

    public:
        log_handler();

        func_ptr add(func _f);
        void remove(func_ptr _f);

        void operator()(const string& _msg);

    };

}

