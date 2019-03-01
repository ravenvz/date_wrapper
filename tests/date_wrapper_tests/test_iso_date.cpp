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

TEST(IsoDate, test_iso_weeknumber)
{
    EXPECT_EQ(16, IsoDate{DateTime::fromYMD(2018, 4, 16)}.weeknum());
    EXPECT_EQ(53, IsoDate{DateTime::fromYMD(2015, 12, 28)}.weeknum());
    EXPECT_EQ(16, IsoDate{DateTime::fromYMD(2018, 4, 22)}.weeknum());
    EXPECT_EQ(53, IsoDate{DateTime::fromYMD(2016, 1, 3)}.weeknum());
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2016, 1, 4)}.weeknum());
    EXPECT_EQ(52, IsoDate{DateTime::fromYMD(2017, 1, 1)}.weeknum());
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2017, 1, 2)}.weeknum());
}

TEST(IsoDate, test_iso_weekyear)
{
    EXPECT_EQ(2018, IsoDate{DateTime::fromYMD(2018, 4, 16)}.year());
    EXPECT_EQ(2015, IsoDate{DateTime::fromYMD(2015, 12, 28)}.year());
    EXPECT_EQ(2018, IsoDate{DateTime::fromYMD(2018, 4, 22)}.year());
    EXPECT_EQ(2015, IsoDate{DateTime::fromYMD(2016, 1, 3)}.year());
    EXPECT_EQ(2016, IsoDate{DateTime::fromYMD(2016, 1, 4)}.year());
    EXPECT_EQ(2016, IsoDate{DateTime::fromYMD(2017, 1, 1)}.year());
    EXPECT_EQ(2017, IsoDate{DateTime::fromYMD(2017, 1, 2)}.year());
}

TEST(IsoDate, test_iso_weekday)
{
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2018, 4, 16)}.weekday());
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2015, 12, 28)}.weekday());
    EXPECT_EQ(7, IsoDate{DateTime::fromYMD(2018, 4, 22)}.weekday());
    EXPECT_EQ(7, IsoDate{DateTime::fromYMD(2016, 1, 3)}.weekday());
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2016, 1, 4)}.weekday());
    EXPECT_EQ(7, IsoDate{DateTime::fromYMD(2017, 1, 1)}.weekday());
    EXPECT_EQ(1, IsoDate{DateTime::fromYMD(2017, 1, 2)}.weekday());
}
