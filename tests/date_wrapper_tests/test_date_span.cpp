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


TEST(DateSpanSuite, returns_duration_in_days)
{
    using namespace dw;
    using namespace std::chrono;

    constexpr Date start{Year{2015}, Month{9}, Day{10}};
    constexpr Date finish{Year{2019}, Month{4}, Day{22}};

    constexpr DateSpan ds{start, finish};

    static_assert(1320 == ds.duration().count());
    static_assert(188 == duration_cast<Weeks>(ds.duration()).count());
    static_assert(43 == duration_cast<Months>(ds.duration()).count());
    static_assert(3 == duration_cast<Years>(ds.duration()).count());
    static_assert(4 == ceil<Years>(ds.duration()).count());
}

TEST(DateSpanSuite, date_span_equality)
{
    using namespace dw;
    constexpr Date start{Year{2019}, Month{1}, Day{7}};
    constexpr Date finish{Year{2018}, Month{3}, Day{1}};

    static_assert(DateSpan{start, finish} == DateSpan{start, finish});
    static_assert(DateSpan{start, start} != DateSpan{start, finish});
}
