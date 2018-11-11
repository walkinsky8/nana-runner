// Created by walkinsky(lyh6188@hotmail.com), 2018/10/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/datetime.h>

#include <nana/runner/istr.h>

nana::runner::datetime::datetime()
{
}

nana::runner::datetime::datetime(date const& _d)
    : date_{ _d }, time_{ 0,0,0 }
{
}

nana::runner::datetime::datetime(time const& _t)
    : date_{ 0,0,0 }, time_{ _t }
{
}

nana::runner::datetime::datetime(date const& _d, time const& _t)
    : date_{_d}, time_{_t}
{
}

nana::runner::datetime::datetime(std::tm const& _t)
    : date_{_t}, time_{_t}
{
}

nana::runner::datetime::datetime(int year, int month, int day, unsigned hour, unsigned minute, unsigned second)
    : date_{ year, month, day }, time_{ hour, minute, second }
{
}

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

void nana::runner::datetime::read(const std::string& _is)
{
    using namespace nana::runner;
    istr p{ _is };
    p.read_until(is_digit);
    istr year = p.read(is_digit, 4);
    p.read_until(is_digit);
    istr month = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr day = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr hour = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr minute = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr second = p.read(is_digit, 2);
    *this = { year.to_int(), month.to_int(), day.to_int(), hour.to_uint(), minute.to_uint(), second.to_uint() };
}

void nana::operator>>(const std::string& _is, date& _v)
{
    using namespace nana::runner;
    istr p{ _is };
    p.read_until(is_digit);
    istr year = p.read(is_digit, 4);
    p.read_until(is_digit);
    istr month = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr day = p.read(is_digit, 2);
    _v = date{ year.to_int(), month.to_int(), day.to_int() };
}

void nana::operator>>(const std::string& _is, time& _v)
{
    using namespace nana::runner;
    istr p{ _is };
    p.read_until(is_digit);
    istr hour = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr minute = p.read(is_digit, 2);
    p.read_until(is_digit);
    istr second = p.read(is_digit, 2);
    _v = time{ hour.to_uint(), minute.to_uint(), second.to_uint() };
}

#endif

