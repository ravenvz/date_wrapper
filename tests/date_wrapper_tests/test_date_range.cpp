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


TEST(DateRangeSuite, returns_duration_in_days)
{
    using namespace dw;
    using namespace std::chrono;

    constexpr Date start{Year{2015}, Month{9}, Day{10}};
    constexpr Date finish{Year{2019}, Month{4}, Day{22}};

    constexpr DateRange date_range{start, finish};

    static_assert(Days{1320} == date_range.duration());
    static_assert(Weeks{188} == duration_cast<Weeks>(date_range.duration()));
    static_assert(Months{43} == duration_cast<Months>(date_range.duration()));
    static_assert(Years{3} == duration_cast<Years>(date_range.duration()));
    static_assert(Years{4} == ceil<Years>(date_range.duration()));
}

TEST(DateRangeSuite, adds_offset_to_range)
{
    using namespace dw;
    using namespace std::chrono_literals;
    constexpr Date start{Year{2015}, Month{9}, Day{10}};
    constexpr Date finish{Year{2019}, Month{4}, Day{22}};
    constexpr DateRange date_range{start, finish};

    constexpr DateRange adjusted{add_offset(date_range, Days{10})};

    static_assert(adjusted.start() == start + Days{10});
    static_assert(adjusted.finish() == finish + Days{10});
}

TEST(DateRangeSuite, date_span_equality)
{
    using namespace dw;
    constexpr Date start{Year{2019}, Month{1}, Day{7}};
    constexpr Date finish{Year{2018}, Month{3}, Day{1}};

    static_assert(DateRange{start, finish} == DateRange{start, finish});
    static_assert(DateRange{start, start} != DateRange{start, finish});
}
