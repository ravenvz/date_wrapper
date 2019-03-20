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

#include <iostream>

using namespace dw;

TEST(IsoDate, test_iso_weeknumber)
{
    static_assert(16 == IsoDate{Date{Year{2018}, Month{4}, Day{16}}}.weeknum());
    static_assert(53
                  == IsoDate{Date{Year{2015}, Month{12}, Day{28}}}.weeknum());
    static_assert(16 == IsoDate{Date{Year{2018}, Month{4}, Day{22}}}.weeknum());
    static_assert(53 == IsoDate{Date{Year{2016}, Month{1}, Day{3}}}.weeknum());
    static_assert(1 == IsoDate{Date{Year{2016}, Month{1}, Day{4}}}.weeknum());
    static_assert(52 == IsoDate{Date{Year{2017}, Month{1}, Day{1}}}.weeknum());
    static_assert(1 == IsoDate{Date{Year{2017}, Month{1}, Day{2}}}.weeknum());
}

TEST(IsoDate, test_iso_weekyear)
{
    static_assert(Year{2018}
                  == IsoDate{Date{Year{2018}, Month{4}, Day{16}}}.year());
    static_assert(Year{2015}
                  == IsoDate{Date{Year{2015}, Month{12}, Day{28}}}.year());
    static_assert(Year{2018}
                  == IsoDate{Date{Year{2018}, Month{4}, Day{22}}}.year());
    static_assert(Year{2015}
                  == IsoDate{Date{Year{2016}, Month{1}, Day{3}}}.year());
    static_assert(Year{2016}
                  == IsoDate{Date{Year{2016}, Month{1}, Day{4}}}.year());
    static_assert(Year{2016}
                  == IsoDate{Date{Year{2017}, Month{1}, Day{1}}}.year());
    static_assert(Year{2017}
                  == IsoDate{Date{Year{2017}, Month{1}, Day{2}}}.year());
}

TEST(IsoDate, test_iso_weekday)
{
    static_assert(Weekday::Monday
                  == IsoDate{Date{Year{2018}, Month{4}, Day{16}}}.weekday());
    static_assert(Weekday::Monday
                  == IsoDate{Date{Year{2015}, Month{12}, Day{28}}}.weekday());
    static_assert(Weekday::Sunday
                  == IsoDate{Date{Year{2018}, Month{4}, Day{22}}}.weekday());
    static_assert(Weekday::Sunday
                  == IsoDate{Date{Year{2016}, Month{1}, Day{3}}}.weekday());
    static_assert(Weekday::Monday
                  == IsoDate{Date{Year{2016}, Month{1}, Day{4}}}.weekday());
    static_assert(Weekday::Sunday
                  == IsoDate{Date{Year{2017}, Month{1}, Day{1}}}.weekday());
    static_assert(Weekday::Monday
                  == IsoDate{Date{Year{2017}, Month{1}, Day{2}}}.weekday());
}
