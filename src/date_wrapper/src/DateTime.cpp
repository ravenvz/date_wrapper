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
#include <iostream>

namespace dw {

DateTime DateTime::addSeconds(long seconds) const
{
    return add(std::chrono::seconds{seconds});
}

DateTime DateTime::addMinutes(long minutes) const
{
    return add(std::chrono::minutes{minutes});
}

DateTime DateTime::addHours(long hours) const
{
    return add(std::chrono::hours{hours});
}

DateTime DateTime::addDays(long days) const { return add(date::days{days}); }

DateTime DateTime::addMonths(int months) const
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

DateTime DateTime::addYears(int years) const { return addMonths(years * 12); }

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
    return (sys_days(other.ymd) - sys_days(ymd)).count();
}

long DateTime::monthsTo(const DateTime& other) const
{
    using namespace date;
    return (year_month{other.ymd.year(), other.ymd.month()}
            - year_month{ymd.year(), ymd.month()})
        .count();
}

long DateTime::yearsTo(const DateTime& other) const
{
    using namespace date;
    return (other.ymd.year() - ymd.year()).count();
}

} // namespace dw
