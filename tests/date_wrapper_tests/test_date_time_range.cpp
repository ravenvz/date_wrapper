/********************************************************************************
**
** Copyright (C) 2016 - 2019 Pavel Pavlov.
**
**
** This file is part of DateWrapper.
**
** DateWrapper is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** DateWrapper is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with DateWrapper.  If not, see <http://www.gnu.org/licenses/>.
**
*********************************************************************************/
#include "gtest/gtest.h"
#include <date_wrapper/date_wrapper.h>

using namespace dw;

TEST(DateTimeRange, returns_correct_durations)
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    constexpr auto start = DateTime{Date{Year{2017}, Month{5}, Day{10}}};
    constexpr DateTime finish{start + 25h};
    constexpr DateTimeRange ts{start, finish};
    constexpr DateTimeRange reversed{finish, start};

    static_assert(25h == ts.duration<hours>());
    static_assert(Days{1} == ts.duration<Days>());
    static_assert(Months{0} == ts.duration<Months>());
    static_assert(1500min == ts.duration<minutes>());
    static_assert(90000s == ts.duration<seconds>());
    static_assert(25h == reversed.duration<hours>());
    static_assert(Days{1} == reversed.duration<Days>());
    static_assert(Months{0} == reversed.duration<Months>());
    static_assert(1500min == reversed.duration<minutes>());
    static_assert(90000s == reversed.duration<seconds>());
}

TEST(DateTimeRange, returns_durations_for_larger_timespans)
{
    constexpr auto start = DateTime{Date{Year{2000}, Month{3}, Day{12}}};
    constexpr auto finish = DateTime{Date{Year{7123}, Month{3}, Day{12}}};
    constexpr DateTimeRange ts{start, finish};

    static_assert(Years{5123} == ts.duration<Years>());
}

TEST(DateTimeRange, can_be_adjusted_by_offset)
{
    using namespace std::chrono_literals;

    constexpr auto start = DateTime{Date{Year{2017}, Month{5}, Day{10}}};
    constexpr DateTime finish{start + 25h};
    constexpr DateTimeRange ts{start, finish};
    constexpr DateTimeRange expected{start + 7200s, start + 25h + 7200s};

    constexpr DateTimeRange adjusted{add_offset(ts, 7200s)};

    static_assert(expected == adjusted);
}

TEST(DateTimeRange, timespan_equality)
{
    using namespace std::chrono_literals;
    constexpr auto start
        = DateTime{Date{Year{2019}, Month{3}, Day{20}}} + 17h + 50min + 34s;
    constexpr DateTime finish{start};

    static_assert(DateTimeRange(start, finish) == DateTimeRange(start, finish));
    static_assert(DateTimeRange(start + 1s, finish)
                  != DateTimeRange(start, finish));
    static_assert(DateTimeRange(start, finish + 1s)
                  != DateTimeRange(start, finish));
}
