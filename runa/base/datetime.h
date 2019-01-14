/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/15
#pragma once

#include <runa/base/_config.h>

#include <nana/datetime.hpp>

namespace runa {

    using nana::date;
    using nana::time;

    class datetime
    {
        date date_;
        time time_;
        unsigned millis_{};

    public:
        datetime();
        datetime(date const& _d);
        datetime(time const& _t);
        datetime(date const& _d, time const& _t);
        datetime(std::tm const& _t, unsigned millis = 0);
        datetime(int year, int month, int day, unsigned hour, unsigned minute, unsigned second, unsigned millis=0);

        static datetime now();
        static int64 milliseconds_since_epoch();

        void set(const std::tm&);

        const date& get_date() const { return date_; }
        const time& get_time() const { return time_; }
        unsigned get_millis() const { return millis_; }

        std::ostream& write(std::ostream& _os) const;
        void read(const std::string& _is);

        std::string& write(std::string& _os) const
        {
            std::ostringstream oss;
            write(oss);
            return _os << oss.str();
        }
        std::string to_string() const
        {
            std::string s;
            write(s);
            return s;
        }

    };
    inline std::ostream& operator<<(std::ostream& _os, const datetime& _v)
    {
        return _v.write(_os);
    }
    inline std::string& operator<<(std::string& _os, const datetime& _v)
    {
        return _v.write(_os);
    }
    inline void operator>>(const std::string& _is, datetime& _v)
    {
        return _v.read(_is);
    }

}

namespace nana {

    void operator>>(const std::string& _is, date& _v);
    std::ostream& operator<<(std::ostream& _os, const date& _v);

    void operator>>(const std::string& _is, time& _v);
    std::ostream& operator<<(std::ostream& _os, const time& _v);

}
