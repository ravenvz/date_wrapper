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
#include "date_wrapper/TimeSpan.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace dw;

TEST(DateTime, test_constructs_correct_object_from_YMD)
{
    DateTime dt = DateTime::fromYMD(2016, 4, 12);
    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(4, dt.month());
    EXPECT_EQ(12, dt.day());
    EXPECT_EQ(0, dt.hour());
    EXPECT_EQ(0, dt.minute());
    EXPECT_EQ(0, dt.second());
}

TEST(DateTime, test_throws_runtime_error_if_invalid_date)
{
    EXPECT_THROW(DateTime::fromYMD(2016, 77, 12), std::runtime_error);
}

TEST(DateTime, test_add_days_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).addDays(9);

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(29, dt.day());
}

TEST(DateTime, test_add_days_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).addDays(-10);

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(10, dt.day());
}

TEST(DateTime, test_add_days_backward_2)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 16);
    DateTime thirtyDaysBack = dt.addDays(-30);

    EXPECT_EQ(2016, thirtyDaysBack.year());
    EXPECT_EQ(4, thirtyDaysBack.month());
    EXPECT_EQ(16, thirtyDaysBack.day());
    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(16, dt.day());
}

TEST(DateTime, test_add_months_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearForward = dt.addMonths(12);

    EXPECT_EQ(2017, yearForward.year());
    EXPECT_EQ(5, yearForward.month());
    EXPECT_EQ(17, yearForward.day());
}

TEST(DateTime, test_add_years_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearForward = dt.addYears(14);

    EXPECT_EQ(2030, yearForward.year());
    EXPECT_EQ(5, yearForward.month());
    EXPECT_EQ(17, yearForward.day());
}

TEST(DateTime, test_add_years_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearBackward = dt.addYears(-16);

    EXPECT_EQ(2000, yearBackward.year());
    EXPECT_EQ(5, yearBackward.month());
    EXPECT_EQ(17, yearBackward.day());
}

TEST(DateTime, test_add_minutes_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesForward = dt.addMinutes(25);

    EXPECT_EQ(2016, minutesForward.year());
    EXPECT_EQ(11, minutesForward.month());
    EXPECT_EQ(26, minutesForward.day());
    EXPECT_EQ(25, minutesForward.minute());
}

TEST(DateTime, test_add_minutes_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesBackward = dt.addMinutes(-25);

    EXPECT_EQ(2016, minutesBackward.year());
    EXPECT_EQ(11, minutesBackward.month());
    EXPECT_EQ(25, minutesBackward.day());
    EXPECT_EQ(35, minutesBackward.minute());
}

TEST(DateTime, test_add_hours_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursForward = dt.addHours(25);

    EXPECT_EQ(2016, hoursForward.year());
    EXPECT_EQ(11, hoursForward.month());
    EXPECT_EQ(27, hoursForward.day());
    EXPECT_EQ(1, hoursForward.hour());
}

TEST(DateTime, test_add_hours_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursBackward = dt.addHours(-25);

    EXPECT_EQ(2016, hoursBackward.year());
    EXPECT_EQ(11, hoursBackward.month());
    EXPECT_EQ(24, hoursBackward.day());
    EXPECT_EQ(23, hoursBackward.hour());
}

TEST(DateTime, test_add_months_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearBack = dt.addMonths(-12);

    EXPECT_EQ(2015, yearBack.year());
    EXPECT_EQ(5, yearBack.month());
    EXPECT_EQ(17, yearBack.day());
}

TEST(DateTime, test_computes_distance_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);

    EXPECT_EQ(0, dt.secondsTo(dt.addSeconds(0)));
    EXPECT_EQ(75, dt.secondsTo(dt.addSeconds(75)));
    EXPECT_EQ(-75, dt.secondsTo(dt.addSeconds(-75)));

    EXPECT_EQ(0, dt.minutesTo(dt.addMinutes(0)));
    EXPECT_EQ(65, dt.minutesTo(dt.addMinutes(65)));
    EXPECT_EQ(-65, dt.minutesTo(dt.addMinutes(-65)));

    EXPECT_EQ(0, dt.hoursTo(dt.addHours(0)));
    EXPECT_EQ(1000, dt.hoursTo(dt.addHours(1000)));
    EXPECT_EQ(-1000, dt.hoursTo(dt.addHours(-1000)));

    EXPECT_EQ(0, dt.daysTo(dt));
    EXPECT_EQ(10, dt.daysTo(dt.addDays(10)));
    EXPECT_EQ(-10, dt.daysTo(dt.addDays(-10)));

    EXPECT_EQ(0, dt.monthsTo(dt.addMonths(0)));
    EXPECT_EQ(12, dt.monthsTo(dt.addMonths(12)));
    EXPECT_EQ(-12, dt.monthsTo(dt.addMonths(-12)));

    EXPECT_EQ(0, dt.yearsTo(dt.addYears(0)));
    EXPECT_EQ(2, dt.yearsTo(dt.addYears(2)));
    EXPECT_EQ(-2, dt.yearsTo(dt.addYears(-2)));
}

TEST(DateTime, test_computes_days_backward)
{
    DateTime currentDt = DateTime::currentDateTime();

    EXPECT_EQ(-11, currentDt.daysTo(currentDt.addDays(-11)));
}

TEST(DateTime, test_returns_correct_weekday)
{
    EXPECT_TRUE(DateTime::Weekday::Monday
          == DateTime::fromYMD(2016, 4, 4).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Tuesday
          == DateTime::fromYMD(2016, 4, 5).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Wednesday
          == DateTime::fromYMD(2016, 4, 6).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Thursday
          == DateTime::fromYMD(2016, 4, 7).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Friday
          == DateTime::fromYMD(2016, 4, 8).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Saturday
          == DateTime::fromYMD(2016, 4, 9).dayOfWeek());
    EXPECT_TRUE(DateTime::Weekday::Sunday
          == DateTime::fromYMD(2016, 4, 10).dayOfWeek());
}

TEST(DateTime, test_ostream_operator)
{
    std::tm tm_struct;
    tm_struct.tm_year = 116;
    tm_struct.tm_mon = 8;
    tm_struct.tm_mday = 21;
    tm_struct.tm_hour = 12;
    tm_struct.tm_min = 59;
    tm_struct.tm_sec = 19;
    std::chrono::system_clock::time_point timepoint;
    to_time_point(tm_struct, timepoint);
    DateTime dt{timepoint};
    std::string expected{"21.09.2016 12:59:19"};
    std::stringstream os;

    os << dt;

    EXPECT_EQ(expected, os.str());
}

TEST(DateTime, test_to_string_handles_date_format)
{
    DateTime dt = DateTime::fromYMD(2016, 9, 21);

    EXPECT_EQ("2016.09.21", dt.toString("yyyy.MM.dd"));
    EXPECT_EQ("201616", dt.toString("yyyyyy"));
    EXPECT_EQ("21", dt.toString("d"));
    EXPECT_EQ("2121", dt.toString("ddd"));
    EXPECT_EQ("9", dt.toString("M"));
    EXPECT_EQ("099", dt.toString("MMM"));
}

TEST(DateTime, test_to_string_handles_time_format)
{
    std::tm tm_struct;
    tm_struct.tm_year = 116;
    tm_struct.tm_mon = 8;
    tm_struct.tm_mday = 21;
    tm_struct.tm_hour = 9;
    tm_struct.tm_min = 7;
    tm_struct.tm_sec = 5;
    std::chrono::system_clock::time_point timepoint;
    to_time_point(tm_struct, timepoint);
    DateTime dt{timepoint};

    EXPECT_EQ("09", dt.toString("hh"));
    EXPECT_EQ("9", dt.toString("h"));
    EXPECT_EQ("07", dt.toString("mm"));
    EXPECT_EQ("077", dt.toString("mmm"));
    EXPECT_EQ("077", dt.toString("mmm"));
    EXPECT_EQ("05", dt.toString("ss"));
    EXPECT_EQ("055", dt.toString("sss"));
    EXPECT_EQ("0907", dt.toString("hhmm"));
}

TEST(DateTime, test_ignores_single_quote_that_has_no_pair)
{
    DateTime dt = DateTime::fromYMD(2016, 9, 21);

    EXPECT_EQ("21-09-2016", dt.toString("dd-'MM-yyyy"));
}

TEST(DateTime, test_threats_input_in_single_quotes_as_text)
{
    DateTime dt = DateTime::fromYMD(2016, 9, 21);

    EXPECT_EQ("2016|what|09ahhMM21", dt.toString("yyyy|'what'|MM'ahhMM'dd"));
}

TEST(DateTime, test_double_single_quotes_replaced_by_single_quote_in_output)
{
    DateTime dt = DateTime::fromYMD(2016, 9, 21);

    EXPECT_EQ("2016'09'21", dt.toString("yyyy''MM''dd"));
}

TEST(DateTime, test_comparison_operators)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 29);
    DateTime before = DateTime::fromYMD(2016, 11, 28);
    DateTime after = DateTime::fromYMD(2016, 11, 30);

    EXPECT_TRUE(dt == dt);
    EXPECT_TRUE(dt <= dt);
    EXPECT_TRUE(dt >= dt);
    EXPECT_TRUE(before <= dt);
    EXPECT_TRUE(before < dt);
    EXPECT_TRUE(after >= dt);
    EXPECT_TRUE(after > dt);
}
