// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#include "stdafx.h"

#include <nana/runner/datetime.h>

nana::runner::datetime::datetime()
{}
nana::runner::datetime::datetime(date const& _d)
    : date_{_d}
{}
nana::runner::datetime::datetime(time const& _t)
    : time_{_t}
{}
nana::runner::datetime::datetime(date const& _d, time const& _t)
    : date_{_d}, time_{_t}
{}
nana::runner::datetime::datetime(std::tm const& _t)
    : date_{_t}, time_{_t}
{}
nana::runner::datetime::datetime(int year, int month, int day, unsigned hour, unsigned minute, unsigned second)
    : date_{ year, month, day }, time_{ hour, minute, second }
{}

void nana::runner::datetime::set(const std::tm& _tm)
{
    date_.set(_tm);
    time_.set(_tm);
}

std::ostream& nana::runner::datetime::write(std::ostream& _os) const
{
    _os << date_ << "_" << time_;
    return _os;
}

std::string& nana::runner::datetime::write(std::string& _os) const
{
    std::ostringstream oss;
    write(oss);
    return _os << oss.str();
}

void nana::runner::datetime::read(const std::string& _is)
{
}

std::ostream& nana::operator<<(std::ostream& _os, const date& _v)
{
    _os << std::setfill('0')
        << std::setw(4) << _v.read().year << "-"
        << std::setw(2) << _v.read().month << "-"
        << std::setw(2) << _v.read().day
        << std::setfill(' ')
        ;
    return _os;
}
std::string& nana::operator<<(std::string& _os, const date& _v)
{
    std::ostringstream oss;
    oss << _v;
    return _os << oss.str();
}
void nana::operator>>(const std::string& _is, date& _v);

std::ostream& nana::operator<<(std::ostream& _os, const time& _v)
{
    _os << std::setfill('0')
        << std::setw(2) << _v.read().hour << ":"
        << std::setw(2) << _v.read().minute << ":"
        << std::setw(2) << _v.read().second
        << std::setfill(' ')
        ;
    return _os;
}
std::string& nana::operator<<(std::string& _os, const time& _v)
{
    std::ostringstream oss;
    oss << _v;
    return _os << oss.str();
}
void nana::operator>>(const std::string& _is, time& _v);
