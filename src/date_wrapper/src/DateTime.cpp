/********************************************************************************
**
** Copyright (C) 2016 Pavel Pavlov.
**
**
** This file is part of SprintTimer.
**
** SprintTimer is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** SprintTimer is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with SprintTimer.  If not, see <http://www.gnu.org/licenses/>.
**
*********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "date_wrapper/DateTime.h"
#include <algorithm>
#include <array>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace {

using namespace dw;

template <typename T>
void pop_back_n(T& container, size_t n)
{
    auto limit = std::min(n, container.size());
    for (size_t i = 0; i < limit; ++i)
        container.pop_back();
}

bool endsWith(const std::string& str, const std::string& suffix);

std::string formatDateTime(const DateTime& dt, std::string&& format);

constexpr std::array<unsigned, 7> mondayFirstTable{
    {6u, 0u, 1u, 2u, 3u, 4u, 5u}};

/* If day is out of range for current month, set it to last day. */
date::year_month_day normalize(date::year_month_day ymd)
{
    using namespace date;
    if (!ymd.ok())
        return ymd.year() / ymd.month() / last;
    return ymd;
}

} // namespace

namespace dw {

DateTime::DateTime(std::chrono::system_clock::time_point timepoint)
    : time{timepoint}
    , ymd{date::year_month_day(date::floor<date::days>(time))}
    , tod{date::make_time(time - date::floor<date::days>(time))}
{
}


/* static */
DateTime DateTime::fromYMD(int year, int month, int day)
{
    date::year_month_day dateYMD{date::year(year) / month / day};
    if (!dateYMD.ok())
        throw std::runtime_error("Invalid date");
    std::chrono::system_clock::time_point tp = date::sys_days(dateYMD);
    return DateTime{tp};
}

/* static */
DateTime DateTime::fromTime_t(std::time_t timeT, int offsetFromUtcInSeconds)
{
    return DateTime{std::chrono::system_clock::from_time_t(timeT)
                    + std::chrono::seconds{offsetFromUtcInSeconds}};
}

/* static */
DateTime DateTime::fromUnixTimestamp(long long timestamp, int offsetFromUtcInSeconds)
{
    return DateTime::fromTimestamp(timestamp, offsetFromUtcInSeconds);
}

/* static */
DateTime DateTime::currentDateTime()
{
    return DateTime{std::chrono::system_clock::now()};
}

/* static */
DateTime DateTime::currentDateTimeLocal()
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(timepoint);
    std::tm localTime = *std::localtime(&t);
    to_time_point(localTime, timepoint);
    return DateTime{timepoint};
}

std::time_t DateTime::toTime_t() const
{
    return std::chrono::system_clock::to_time_t(time);
}

DateTime DateTime::addSeconds(long seconds) const
{
    return DateTime{time + std::chrono::seconds{seconds}};
}

DateTime DateTime::addMinutes(long minutes) const
{
    return DateTime{time + std::chrono::minutes{minutes}};
}

DateTime DateTime::addHours(long hours) const
{
    return DateTime{time + std::chrono::hours{hours}};
}

DateTime DateTime::addDays(long days) const
{
    return DateTime{time + date::days{days}};
}

DateTime DateTime::addMonths(long months) const
{
    using namespace date;
    using namespace std::chrono;
    auto y = year_month{date::year(year()), date::month(month())}
        + date::months{months};
    auto t = year_month_day{y.year(), y.month(), date::day(day())};
    t = normalize(t);
    auto d
        = sys_days{t} + hours{hour()} + minutes{minute()} + seconds{second()};

    return DateTime{d};
}

DateTime DateTime::addYears(long years) const
{
    return DateTime{time + date::months{years * 12}};
}

long long DateTime::secondsTo(const DateTime& other) const
{
    return std::chrono::duration_cast<std::chrono::seconds>(other.time - time)
        .count();
}

long DateTime::minutesTo(const DateTime& other) const
{
    return std::chrono::duration_cast<std::chrono::minutes>(other.time - time)
        .count();
}

long DateTime::hoursTo(const DateTime& other) const
{
    return std::chrono::duration_cast<std::chrono::hours>(other.time - time)
        .count();
}

long DateTime::daysTo(const DateTime& other) const
{
    using namespace date;
    return (floor<days>(other.time) - floor<days>(this->time)).count();
}

long DateTime::monthsTo(const DateTime& other) const
{
    using namespace date;
    return (floor<months>(other.time) - floor<months>(this->time)).count();
}

long DateTime::yearsTo(const DateTime& other) const
{
    using namespace date;
    return (floor<years>(other.time) - floor<years>(this->time)).count();
}

std::chrono::system_clock::time_point DateTime::chronoTimepoint() const
{
    return time;
}

long long DateTime::unix_timestamp() const
{
    return timestamp<std::chrono::seconds>();
}

int DateTime::year() const { return int(ymd.year()); }

unsigned DateTime::month() const { return unsigned(ymd.month()); }

unsigned DateTime::day() const { return unsigned(ymd.day()); }

long DateTime::hour() const { return tod.hours().count(); }

long DateTime::minute() const { return tod.minutes().count(); }

long long DateTime::second() const { return tod.seconds().count(); }

DateTime::Weekday DateTime::dayOfWeek() const
{
    auto dayNumber
        = mondayFirstTable[static_cast<unsigned>(date::weekday(ymd))];
    return static_cast<DateTime::Weekday>(dayNumber);
}

std::string DateTime::toString(std::string format) const
{
    return formatDateTime(*this, std::move(format));
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << std::setfill('0') << std::setw(2) << dt.day() << "."
       << std::setfill('0') << std::setw(2) << dt.month() << "." << dt.year()
       << " " << std::setfill('0') << std::setw(2) << dt.hour() << ":"
       << std::setfill('0') << std::setw(2) << dt.minute() << ":"
       << std::setfill('0') << std::setw(2) << dt.second();
    return os;
}

} // namespace dw

namespace {

bool endsWith(const std::string& str, const std::string& suffix)
{
    if (suffix.size() > str.size())
        return false;
    return std::equal(suffix.crbegin(), suffix.crend(), str.crbegin());
}

std::string formatDateTime(const DateTime& dt, std::string&& format)
{
    std::stringstream ss;

    std::string f{std::move(format)};
    std::reverse(f.begin(), f.end());

    while (!f.empty()) {
        if (endsWith(f, "''")) {
            ss << "'";
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "'")) {
            pop_back_n(f, 1);
            auto m = f.find_last_of("'");
            if (m != std::string::npos) {
                while (!endsWith(f, "'")) {
                    ss << f.back();
                    f.pop_back();
                }
                f.pop_back();
            }
        }
        else if (endsWith(f, "yyyy")) {
            ss << std::setfill('0') << std::setw(4) << dt.year();
            pop_back_n(f, 4);
        }
        else if (endsWith(f, "yy")) {
            ss << std::setfill('0') << std::setw(2) << dt.year() % 100;
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "MM")) {
            ss << std::setfill('0') << std::setw(2) << dt.month();
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "M")) {
            ss << dt.month();
            pop_back_n(f, 1);
        }
        else if (endsWith(f, "dd")) {
            ss << std::setfill('0') << std::setw(2) << dt.day();
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "d")) {
            ss << dt.day();
            pop_back_n(f, 1);
        }
        else if (endsWith(f, "hh")) {
            ss << std::setfill('0') << std::setw(2) << dt.hour();
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "h")) {
            ss << dt.hour();
            pop_back_n(f, 1);
        }
        else if (endsWith(f, "mm")) {
            ss << std::setfill('0') << std::setw(2) << dt.minute();
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "m")) {
            ss << dt.minute();
            pop_back_n(f, 1);
        }
        else if (endsWith(f, "ss")) {
            ss << std::setfill('0') << std::setw(2) << dt.second();
            pop_back_n(f, 2);
        }
        else if (endsWith(f, "s")) {
            ss << dt.second();
            pop_back_n(f, 1);
        }
        else {
            ss << f.back();
            f.pop_back();
        }
    }

    return ss.str();
}
} // namespace
