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
using namespace dw::utils;
using namespace std::chrono_literals;
using namespace std::chrono;

TEST(DateTime, construct_from_unix_timestamp)
{
    constexpr DateTime expected{DateTime{Date{Year{2017}, Month{5}, Day{1}}}
                                + 13h + 10min + 20s};
    constexpr DateTime dt{std::chrono::system_clock::time_point{1493644220s}};

    static_assert(expected == dt);
}

TEST(DateTime, construct_from_timestamp)
{
    constexpr DateTime expected{DateTime{Date{Year{2017}, Month{5}, Day{1}}}
                                + 13h + 10min + 20s};

    constexpr DateTime dt{
        std::chrono::system_clock::time_point{1493644220000ms}};

    static_assert(expected == dt);
}

TEST(DateTime, constructs_from_timestamp_with_low_precision)
{
    constexpr DateTime expected{DateTime{Date{Year{2017}, Month{5}, Day{1}}}};

    constexpr DateTime dt{std::chrono::system_clock::time_point{414888h}};

    static_assert(expected == dt);
}

TEST(DateTime, constructs_from_date)
{
    constexpr Date date{Year{2016}, Month{4}, Day{12}};

    constexpr DateTime dt{date};

    static_assert(Year{2016} == dt.year());
    static_assert(Month{4} == dt.month());
    static_assert(Day{12} == dt.day());
    static_assert(0h == dt.hour());
    static_assert(0min == dt.minute());
    static_assert(0s == dt.second());
}

TEST(DateTime, normalizes_time_since_midnight_when_contructing)
{
    constexpr auto dt = DateTime{Date{Year{2019}, Month{3}, Day{20}}, 26h};
    constexpr auto expected
        = DateTime{Date{Year{2019}, Month{3}, Day{21}}} + 2h;

    static_assert(expected == dt);
}

TEST(DateTime, adds_days)
{
    constexpr DateTime dt{Date{Year{2016}, Month{2}, Day{20}}};
    constexpr DateTime expected{Date{Year{2016}, Month{2}, Day{29}}};

    constexpr DateTime modified{dt + Days{9}};

    static_assert(expected == modified);
}

TEST(DateTime, subtracts_days)
{
    constexpr DateTime dt{Date{Year{2016}, Month{5}, Day{16}}};
    constexpr DateTime expected{Date{Year{2016}, Month{4}, Day{16}}};

    constexpr DateTime modified{dt - Days{30}};

    static_assert(expected == modified);
}

TEST(DateTime, adds_months)
{
    constexpr DateTime dt{Date{Year{2019}, Month{3}, Day{1}}};
    constexpr auto expected
        = utils::from_ymd(date::year{2019} / date::March / 1 + date::months{1});

    constexpr DateTime modified{dt + Months{1}};

    static_assert(expected == modified);
}

TEST(DateTime, subtracting_custom_duration)
{
    constexpr auto dt
        = DateTime{Date{Year{2019}, Month{3}, Day{12}}} + 20h + 20min + 20s;
    constexpr auto expected
        = DateTime{Date{Year{2019}, Month{3}, Day{11}}} + 22h + 10min + 15s;

    constexpr DateTime modified{dt - 22h - 10min - 5s};

    static_assert(expected == modified);
}

TEST(DateTime, subtracting_calendric_months_results_in_latest_valid_date)
{
    constexpr auto dt
        = DateTime{Date{Year{2017}, Month{3}, Day{1}}} + 23h + 11min + 4s;
    constexpr auto expected
        = DateTime{Date{Year{2016}, Month{4}, Day{1}}} + 23h + 11min + 4s;

    constexpr DateTime modified{dt - Months{11}};

    static_assert(expected == modified);
}

TEST(DateTime, adds_years)
{
    constexpr auto dt
        = DateTime{Date{Year{2016}, Month{2}, Day{29}}} + 17h + 25min + 30s;
    constexpr auto expected
        = DateTime{Date{Year{5031}, Month{2}, Day{28}}} + 17h + 25min + 30s;

    constexpr DateTime modified{dt + Years{3015}};

    EXPECT_EQ(expected, modified);
    // static_assert(expected == modified);
}

TEST(DateTime, subtracts_years)
{
    constexpr auto dt
        = DateTime{Date{Year{2030}, Month{2}, Day{28}}} + 10h + 20min + 11s;
    constexpr auto expected
        = DateTime{Date{Year{2016}, Month{2}, Day{28}}} + 10h + 20min + 11s;

    constexpr DateTime modified{dt - Years{14}};

    static_assert(expected == modified);
}

TEST(DateTime, adds_minutes)
{
    constexpr DateTime dt{Date{Year{2016}, Month{11}, Day{26}}};

    constexpr auto modified = dt + 5min;

    static_assert(Year{2016} == modified.year());
    static_assert(Month{11} == modified.month());
    static_assert(Day{26} == modified.day());
    static_assert(0h == modified.hour());
    static_assert(5min == modified.minute());
    static_assert(0s == modified.second());
}

TEST(DateTime, subtracts_minutes)
{
    constexpr DateTime dt{Date{Year{2016}, Month{11}, Day{26}}};

    constexpr auto modified = dt - 25min;

    static_assert(Year{2016} == modified.year());
    static_assert(Month{11} == modified.month());
    static_assert(Day{25} == modified.day());
    static_assert(23h == modified.hour());
    static_assert(35min == modified.minute());
    static_assert(0s == modified.second());
}

TEST(DateTime, adds_hours)
{
    constexpr DateTime dt{Date{Year{2016}, Month{11}, Day{26}}};

    constexpr auto modified = dt + 25h;

    static_assert(Year{2016} == modified.year());
    static_assert(Month{11} == modified.month());
    static_assert(Day{27} == modified.day());
    static_assert(1h == modified.hour());
    static_assert(0min == modified.minute());
    static_assert(0s == modified.second());
}

TEST(DateTime, subtracts_hours)
{
    constexpr DateTime dt{Date{Year{2016}, Month{11}, Day{26}}};

    constexpr DateTime modified = dt - 25h;

    static_assert(Year{2016} == modified.year());
    static_assert(Month{11} == modified.month());
    static_assert(Day{24} == modified.day());
    static_assert(23h == modified.hour());
    static_assert(0min == modified.minute());
    static_assert(0s == modified.second());
}

TEST(DateTime, returns_correct_weekday)
{
    static_assert(Weekday::Monday
                  == DateTime{Date{Year{2016}, Month{4}, Day{4}}}.weekday());
    static_assert(Weekday::Tuesday
                  == DateTime{Date{Year{2016}, Month{4}, Day{5}}}.weekday());
    static_assert(Weekday::Wednesday
                  == DateTime{Date{Year{2016}, Month{4}, Day{6}}}.weekday());
    static_assert(Weekday::Thursday
                  == DateTime{Date{Year{2016}, Month{4}, Day{7}}}.weekday());
    static_assert(Weekday::Friday
                  == DateTime{Date{Year{2016}, Month{4}, Day{8}}}.weekday());
    static_assert(Weekday::Saturday
                  == DateTime{Date{Year{2016}, Month{4}, Day{9}}}.weekday());
    static_assert(Weekday::Sunday
                  == DateTime{Date{Year{2016}, Month{4}, Day{10}}}.weekday());
}

TEST(DateTime, ostream_operator)
{
    constexpr auto dt
        = DateTime{Date{Year{2016}, Month{9}, Day{21}}} + 12h + 59min + 19s;
    std::string expected{"21.09.2016 12:59:19"};
    std::stringstream os;

    os << dt;

    EXPECT_EQ(expected, os.str());
}

TEST(DateTime, to_string_handles_date_format)
{
    constexpr DateTime dt{Date{Year{2016}, Month{9}, Day{21}}};

    EXPECT_EQ("2016.09.21", to_string(dt, "yyyy.MM.dd"));
    EXPECT_EQ("201616", to_string(dt, "yyyyyy"));
    EXPECT_EQ("21", to_string(dt, "d"));
    EXPECT_EQ("2121", to_string(dt, "ddd"));
    EXPECT_EQ("9", to_string(dt, "M"));
    EXPECT_EQ("099", to_string(dt, "MMM"));
}

TEST(DateTime, to_string_handles_time_format)
{
    constexpr auto dt
        = DateTime{Date{Year{2016}, Month{9}, Day{21}}} + 9h + 7min + 5s;

    EXPECT_EQ("09", to_string(dt, "hh"));
    EXPECT_EQ("9", to_string(dt, "h"));
    EXPECT_EQ("07", to_string(dt, "mm"));
    EXPECT_EQ("077", to_string(dt, "mmm"));
    EXPECT_EQ("077", to_string(dt, "mmm"));
    EXPECT_EQ("05", to_string(dt, "ss"));
    EXPECT_EQ("055", to_string(dt, "sss"));
    EXPECT_EQ("0907", to_string(dt, "hhmm"));
}

TEST(DateTime, ignores_single_quote_that_has_no_pair)
{
    constexpr DateTime dt{Date{Year{2016}, Month{9}, Day{21}}};

    EXPECT_EQ("21-09-2016", to_string(dt, "dd-'MM-yyyy"));
}

TEST(DateTime, threats_input_in_single_quotes_as_text)
{
    constexpr DateTime dt{Date{Year{2016}, Month{9}, Day{21}}};

    EXPECT_EQ("2016|what|09ahhMM21", to_string(dt, "yyyy|'what'|MM'ahhMM'dd"));
}

TEST(DateTime, double_single_quotes_replaced_by_single_quote_in_output)
{
    constexpr DateTime dt{Date{Year{2016}, Month{9}, Day{21}}};

    EXPECT_EQ("2016'09'21", to_string(dt, "yyyy''MM''dd"));
}

TEST(DateTime, test_comparison_operators)
{
    constexpr auto dt = DateTime{Date{Year{8032}, Month{11}, Day{29}}};
    constexpr auto before = DateTime{Date{Year{8032}, Month{11}, Day{28}}};
    constexpr auto after = DateTime{Date{Year{8032}, Month{11}, Day{30}}};

    static_assert(dt == dt);
    static_assert(dt <= dt);
    static_assert(dt >= dt);
    static_assert(before <= dt);
    static_assert(before < dt);
    static_assert(after >= dt);
    static_assert(after > dt);
    static_assert(dt < dt + 1s);
    static_assert(dt + 1s > dt);
}

TEST(DateTime, returns_unix_timestamp)
{
    constexpr auto dt
        = DateTime{Date{Year{2017}, Month{5}, Day{1}}} + 13h + 10min + 20s;

    static_assert(
        1493644220s
        == to_time_point<std::chrono::seconds>(dt).time_since_epoch());
}

TEST(DateTime, returns_timestamp_in_years)
{
    constexpr auto dt = DateTime{Date{Year{5070}, Month{4}, Day{1}}};

    static_assert(Years{3100} == to_time_point<Years>(dt).time_since_epoch());
    static_assert(
        97834348800s
        == to_time_point<std::chrono::seconds>(dt).time_since_epoch());
}

