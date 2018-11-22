// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/_config.h>

#include <nana/runner/base_types.h>

#include <nana/runner/util.h>

#include <nana/runner/mt_thread.h>
#include <nana/runner/mt_queue.h>
#include <nana/runner/mt_vector.h>

#define NAR_LOG(x)          NAR_LOG_INFO(x)

#define NAR_LOG_VAR(x)      NAR_LOG_NV(#x, x)
#define NAR_LOG_NV(n, v)    NAR_LOG_DEBUG(n << " = " << v)

#define NAR_LOG_EXCPT(x)    NAR_LOG_(nana::runner::LL_EXCEPTION, x)
#define NAR_LOG_ERROR(x)    NAR_LOG_(nana::runner::LL_ERROR, x)
#define NAR_LOG_WARN(x)     NAR_LOG_(nana::runner::LL_WARN, x)
#define NAR_LOG_INFO(x)     NAR_LOG_(nana::runner::LL_INFO, x)
#define NAR_LOG_DEBUG(x)    NAR_LOG_(nana::runner::LL_DEBUG, x)
#define NAR_LOG_VERBOSE(x)  NAR_LOG_(nana::runner::LL_VERBOSE, x)

#define NAR_LOG_(ll, x)     nana::runner::log(ll, NAR_CURRENT()) << x

#define NAR_CURRENT()       nana::runner::current_info{__FILE__, __LINE__, __FUNCTION__}

#define NAR_THROW_ERROR(e, x)  throw e{(nana::runner::out()<<NAR_CURRENT()<<" "<<#e<<": "<<x).str().c_str()}

namespace nana::runner {

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
        LL_UNKNOWN = -1
    };
    using enum_log_level = enum_<log_level, LL_UNKNOWN>;

    struct log_head
    {
        datetime dt_;
        log_level ll_;
        current_info current_;

        log_head() = default;
        log_head(log_level _ll, current_info const& _current);

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
        log(log_level _ll, current_info const& _current);
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

