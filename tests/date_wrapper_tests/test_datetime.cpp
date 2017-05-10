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
#include "gtest/gtest.h"
#include <iostream>

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

TEST(DateTime, test_add_days_forward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).addDays(9);

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(29, dt.day());
}

TEST(DateTime, test_add_days_backward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).addDays(-10);

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(10, dt.day());
}

TEST(DateTime, test_add_days_backward_deprecated_2)
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

TEST(DateTime, test_add_months_backward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearBack = dt.addMonths(-12);

    EXPECT_EQ(2015, yearBack.year());
    EXPECT_EQ(5, yearBack.month());
    EXPECT_EQ(17, yearBack.day());
}

TEST(DateTime, test_add_months_backward_deprecated_2)
{
    DateTime dt = DateTime::fromYMD(2017, 3, 1);
    DateTime elevenMonthsBack = dt.addMonths(-11);

    EXPECT_EQ(2016, elevenMonthsBack.year());
    EXPECT_EQ(4, elevenMonthsBack.month());
    EXPECT_EQ(1, elevenMonthsBack.day());
}

TEST(DateTime, test_add_months_normalizes_day_deprecated)
{
    DateTime dt = DateTime::fromYMD(2017, 1, 30);
    DateTime one_month_forward = dt.addMonths(1);

    EXPECT_EQ(2017, one_month_forward.year());
    EXPECT_EQ(2, one_month_forward.month());
    EXPECT_EQ(28, one_month_forward.day());
}

TEST(DateTime, test_add_months_forward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearForward = dt.addMonths(12);

    EXPECT_EQ(2017, yearForward.year());
    EXPECT_EQ(5, yearForward.month());
    EXPECT_EQ(17, yearForward.day());
}

TEST(DateTime, test_add_years_forward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearForward = dt.addYears(14);

    EXPECT_EQ(2030, yearForward.year());
    EXPECT_EQ(5, yearForward.month());
    EXPECT_EQ(17, yearForward.day());
}

TEST(DateTime, test_add_years_backward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearBackward = dt.addYears(-16);

    EXPECT_EQ(2000, yearBackward.year());
    EXPECT_EQ(5, yearBackward.month());
    EXPECT_EQ(17, yearBackward.day());
}

TEST(DateTime, test_add_minutes_forward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesForward = dt.addMinutes(25);

    EXPECT_EQ(2016, minutesForward.year());
    EXPECT_EQ(11, minutesForward.month());
    EXPECT_EQ(26, minutesForward.day());
    EXPECT_EQ(25, minutesForward.minute());
}

TEST(DateTime, test_add_minutes_backward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesBackward = dt.addMinutes(-25);

    EXPECT_EQ(2016, minutesBackward.year());
    EXPECT_EQ(11, minutesBackward.month());
    EXPECT_EQ(25, minutesBackward.day());
    EXPECT_EQ(35, minutesBackward.minute());
}

TEST(DateTime, test_add_hours_forward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursForward = dt.addHours(25);

    EXPECT_EQ(2016, hoursForward.year());
    EXPECT_EQ(11, hoursForward.month());
    EXPECT_EQ(27, hoursForward.day());
    EXPECT_EQ(1, hoursForward.hour());
}

TEST(DateTime, test_add_hours_backward_deprecated)
{
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursBackward = dt.addHours(-25);

    EXPECT_EQ(2016, hoursBackward.year());
    EXPECT_EQ(11, hoursBackward.month());
    EXPECT_EQ(24, hoursBackward.day());
    EXPECT_EQ(23, hoursBackward.hour());
}

TEST(DateTime, test_computes_distance_deprecated)
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

TEST(DateTime, test_computes_days_backward_deprecated)
{
    DateTime currentDt = DateTime::currentDateTime();

    EXPECT_EQ(-11, currentDt.daysTo(currentDt.addDays(-11)));
}

TEST(DateTime, test_add_days_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).add(DateTime::Days{9});

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(29, dt.day());
}

TEST(DateTime, test_add_days_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 2, 20).add(DateTime::Days{-10});

    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(2, dt.month());
    EXPECT_EQ(10, dt.day());
}

TEST(DateTime, test_add_days_backward_2)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 16);
    DateTime thirtyDaysBack = dt.add(DateTime::Days{-30});

    EXPECT_EQ(2016, thirtyDaysBack.year());
    EXPECT_EQ(4, thirtyDaysBack.month());
    EXPECT_EQ(16, thirtyDaysBack.day());
    EXPECT_EQ(2016, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(16, dt.day());
}

TEST(DateTime, test_add_months_backward_2)
{
    DateTime dt = DateTime::fromYMD(2017, 3, 1);
    DateTime elevenMonthsBack = dt.add(DateTime::Months{-11});

    EXPECT_EQ(2016, elevenMonthsBack.year());
    EXPECT_EQ(4, elevenMonthsBack.month());
    EXPECT_EQ(1, elevenMonthsBack.day());
}

TEST(DateTime, test_add_years_forward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearForward = dt.add(DateTime::Years{14});

    EXPECT_EQ(2030, yearForward.year());
    EXPECT_EQ(5, yearForward.month());
    EXPECT_EQ(17, yearForward.day());
}

TEST(DateTime, test_add_years_backward)
{
    DateTime dt = DateTime::fromYMD(2016, 5, 17);
    DateTime yearBackward = dt.add(DateTime::Years{-16});

    EXPECT_EQ(2000, yearBackward.year());
    EXPECT_EQ(5, yearBackward.month());
    EXPECT_EQ(17, yearBackward.day());
}

TEST(DateTime, test_add_minutes_forward)
{
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesForward = dt.add(25min);

    EXPECT_EQ(2016, minutesForward.year());
    EXPECT_EQ(11, minutesForward.month());
    EXPECT_EQ(26, minutesForward.day());
    EXPECT_EQ(25, minutesForward.minute());
}

TEST(DateTime, test_add_minutes_backward)
{
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime minutesBackward = dt.add(-25min);

    EXPECT_EQ(2016, minutesBackward.year());
    EXPECT_EQ(11, minutesBackward.month());
    EXPECT_EQ(25, minutesBackward.day());
    EXPECT_EQ(35, minutesBackward.minute());
}

TEST(DateTime, test_add_hours_forward)
{
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursForward = dt.add(25h);

    EXPECT_EQ(2016, hoursForward.year());
    EXPECT_EQ(11, hoursForward.month());
    EXPECT_EQ(27, hoursForward.day());
    EXPECT_EQ(1, hoursForward.hour());
}

TEST(DateTime, test_difference_between)
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using namespace date;
    DateTime dt = DateTime::fromYMD(2017, 5, 1);
    DateTime other = dt.add(-25min);

    EXPECT_EQ(1500, other.differenceBetween<seconds>(dt).count());
    EXPECT_EQ(-1500, dt.differenceBetween<seconds>(other).count());
    EXPECT_EQ(25, other.differenceBetween<minutes>(dt).count());
    EXPECT_EQ(-25, dt.differenceBetween<minutes>(other).count());
    // rounding towards zero
    EXPECT_EQ(0, other.differenceBetween<hours>(dt).count());
    EXPECT_EQ(0, dt.differenceBetween<hours>(other).count());
    EXPECT_EQ(0, other.differenceBetween<DateTime::Days>(dt).count());
    EXPECT_EQ(0, dt.differenceBetween<DateTime::Days>(other).count());
    EXPECT_EQ(0, other.differenceBetween<DateTime::Months>(dt).count());
    EXPECT_EQ(0, dt.differenceBetween<DateTime::Months>(other).count());
}

TEST(DateTime, test_discrete_days_to)
{
    using namespace std::chrono;
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2017, 5, 10);

    EXPECT_EQ(0, dt.discreteDaysTo(dt.add(1h)));
    EXPECT_EQ(-1, dt.discreteDaysTo(dt.add(-1h)));
    EXPECT_EQ(1, dt.discreteDaysTo(dt.add(24h)));
}

TEST(DateTime, test_discrete_months_to)
{
    using namespace std::chrono;
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2017, 5, 10);

    EXPECT_EQ(0, dt.discreteMonthsTo(dt));
    EXPECT_EQ(1, dt.discreteMonthsTo(dt.add(DateTime::Days{31})));
    EXPECT_EQ(-1, dt.discreteMonthsTo(dt.add(DateTime::Days{-31})));
}

TEST(DateTime, test_discrete_years_to)
{
    using namespace std::chrono;
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2017, 5, 10);

    EXPECT_EQ(0, dt.discreteYearsTo(dt));
    EXPECT_EQ(1, dt.discreteYearsTo(dt.add(DateTime::Months{12})));
    EXPECT_EQ(-1, dt.discreteYearsTo(dt.add(DateTime::Months{-12})));
}

TEST(DateTime, test_add_hours_backward)
{
    using namespace std::chrono_literals;
    DateTime dt = DateTime::fromYMD(2016, 11, 26);
    DateTime hoursBackward = dt.add(-25h);

    EXPECT_EQ(2016, hoursBackward.year());
    EXPECT_EQ(11, hoursBackward.month());
    EXPECT_EQ(24, hoursBackward.day());
    EXPECT_EQ(23, hoursBackward.hour());
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

TEST(DateTime, test_construct_from_unix_timestamp)
{
    DateTime dt = DateTime::fromUnixTimestamp(1493644220);

    EXPECT_EQ(2017, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(1, dt.day());
    EXPECT_EQ(13, dt.hour());
    EXPECT_EQ(10, dt.minute());
    EXPECT_EQ(20, dt.second());
}

TEST(DateTime, test_construct_from_timestamp_with_given_precision)
{
    DateTime dt
        = DateTime::fromTimestamp<std::chrono::milliseconds>(1493644220000);

    EXPECT_EQ(2017, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(1, dt.day());
    EXPECT_EQ(13, dt.hour());
    EXPECT_EQ(10, dt.minute());
    EXPECT_EQ(20, dt.second());
}

TEST(DateTime, test_constructs_from_timestamp_of_very_low_precision)
{
    DateTime dt = DateTime::fromTimestamp<std::chrono::hours>(414888);

    EXPECT_EQ(2017, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(1, dt.day());
    EXPECT_EQ(0, dt.hour());
    EXPECT_EQ(0, dt.minute());
    EXPECT_EQ(0, dt.second());
}

TEST(None, test_construct_from_timestamp_with_utc_offset)
{
    DateTime dt = DateTime::fromTimestamp<std::chrono::hours>(414888, 10800);

    EXPECT_EQ(2017, dt.year());
    EXPECT_EQ(5, dt.month());
    EXPECT_EQ(1, dt.day());
    EXPECT_EQ(3, dt.hour());
    EXPECT_EQ(0, dt.minute());
    EXPECT_EQ(0, dt.second());
}

TEST(DateTime, test_returns_unix_timestamp)
{
    std::tm tm_struct;
    tm_struct.tm_year = 117;
    tm_struct.tm_mon = 4;
    tm_struct.tm_mday = 1;
    tm_struct.tm_hour = 13;
    tm_struct.tm_min = 10;
    tm_struct.tm_sec = 20;
    std::chrono::system_clock::time_point timepoint;
    to_time_point(tm_struct, timepoint);
    DateTime dt{timepoint};

    EXPECT_EQ(1493644220, dt.unix_timestamp());
}
