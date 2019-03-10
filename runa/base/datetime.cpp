/**
*	Runa C++ Library
*	Copyright (c) 2017-2019 walkinsky:lyh6188(at)hotmail(dot)com
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*/
// Created at 2018/10/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <runa/base/datetime.h>

#include <runa/base/istr.h>

runa::datetime::datetime()
{
}

runa::datetime::datetime(date const& _d)
    : date_{ _d }, time_{ 0,0,0 }
{
}

runa::datetime::datetime(time const& _t)
    : date_{ 0,0,0 }, time_{ _t }
{
}

runa::datetime::datetime(date const& _d, time const& _t)
    : date_{_d}, time_{_t}
{
}

runa::datetime::datetime(std::tm const& _t, unsigned millis)
    : date_{_t}, time_{_t}, millis_{ millis }
{
}

runa::datetime::datetime(int year, int month, int day, unsigned hour, unsigned minute, unsigned second, unsigned millis)
    : date_{ year, month, day }, time_{ hour, minute, second }, millis_{ millis }
{
}

runa::datetime runa::datetime::now()
{
    using namespace std::chrono;
    auto curr = system_clock::now();
    auto ttt = system_clock::to_time_t(curr);
    tm tmval;
    #ifdef _MSC_VER
    localtime_s(&tmval, &ttt);
    #else
    tmval = *localtime(&ttt);
    #endif
    auto ms = time_point_cast<milliseconds>(curr);
    datetime retval{ tmval, static_cast<uint>(ms.time_since_epoch().count()%1000) };
    return retval;
}

runa::int64 runa::datetime::milliseconds_since_epoch()
{
    using namespace std::chrono;
    return time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
}

void runa::datetime::set(const std::tm& _tm)
{
    date_.set(_tm);
    time_.set(_tm);
}

std::ostream& runa::datetime::write(std::ostream& _os) const
{
    _os << date_;
    _os << "_" << time_;
    _os << "." << std::setfill('0')
        << std::setw(3) << millis_
        << std::setfill(' ')
        ;
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

void runa::datetime::read(const std::string& _is)
{
    using namespace runa;
    istr p{ _is };
    p.read_until(is_digit); istr year = p.read(is_digit, 4);
    p.read_until(is_digit); istr month = p.read(is_digit, 2);
    p.read_until(is_digit); istr day = p.read(is_digit, 2);
    p.read_until(is_digit); istr hour = p.read(is_digit, 2);
    p.read_until(is_digit); istr minute = p.read(is_digit, 2);
    p.read_until(is_digit); istr second = p.read(is_digit, 2);
    p.read_until(is_digit); istr millisecond = p.read(is_digit, 3);
    *this = { year.to_int(), month.to_int(), day.to_int(), hour.to_uint(), minute.to_uint(), second.to_uint(), millisecond.to_uint() };
}

void nana::operator>>(const std::string& _is, date& _v)
{
    using namespace runa;
    istr p{ _is };
    p.read_until(is_digit); istr year = p.read(is_digit, 4);
    p.read_until(is_digit); istr month = p.read(is_digit, 2);
    p.read_until(is_digit); istr day = p.read(is_digit, 2);
    _v = date{ year.to_int(), month.to_int(), day.to_int() };
}

void nana::operator>>(const std::string& _is, time& _v)
{
    using namespace runa;
    istr p{ _is };
    p.read_until(is_digit); istr hour = p.read(is_digit, 2);
    p.read_until(is_digit); istr minute = p.read(is_digit, 2);
    p.read_until(is_digit); istr second = p.read(is_digit, 2);
    _v = time{ hour.to_uint(), minute.to_uint(), second.to_uint() };
}

#endif

