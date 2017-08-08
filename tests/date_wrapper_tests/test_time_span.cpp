/********************************************************************************
**
** Copyright (C) 2016, 2017 Pavel Pavlov.
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
#include "date_wrapper/TimeSpan.h"
#include "gtest/gtest.h"

using namespace dw;

TEST(TimeSpan, test_duration)
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    DateTime start = DateTime::fromYMD(2017, 5, 10);
    DateTime finish = start.add(25h);
    TimeSpan ts{start, finish};
    TimeSpan reversed{finish, start};

    EXPECT_EQ(25, ts.duration<hours>().count());
    EXPECT_EQ(1, ts.duration<DateTime::Days>().count());
    EXPECT_EQ(0, ts.duration<DateTime::Months>().count());
    EXPECT_EQ(1500, ts.duration<minutes>().count());
    EXPECT_EQ(90000, ts.duration<seconds>().count());
    EXPECT_EQ(25, reversed.duration<hours>().count());
    EXPECT_EQ(1, reversed.duration<DateTime::Days>().count());
    EXPECT_EQ(0, reversed.duration<DateTime::Months>().count());
    EXPECT_EQ(1500, reversed.duration<minutes>().count());
    EXPECT_EQ(90000, reversed.duration<seconds>().count());
}
