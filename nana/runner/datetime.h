// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#pragma once

#include <nana/runner/_config.h>

#include <nana/datetime.hpp>

namespace runa {

    using nana::date;
    using nana::time;

    class datetime
    {
        date date_;
        time time_;

    public:
        datetime();
        datetime(date const& _d);
        datetime(time const& _t);
        datetime(date const& _d, time const& _t);
        datetime(std::tm const& _t);
        datetime(int year, int month, int day, unsigned hour, unsigned minute, unsigned second);

        void set(const std::tm&);

        const date& get_date() const { return date_; }
        const time& get_time() const { return time_; }

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
