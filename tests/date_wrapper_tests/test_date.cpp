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
#include "date_wrapper/date_wrapper.h"
#include "gtest/gtest.h"

using namespace dw;

TEST(Date, constructs_from_YMD)
{
    constexpr Date date{Year{2019}, Month{2}, Day{23}};

    static_assert(Year{2019} == date.year());
    static_assert(Month{2} == date.month());
    static_assert(Day{23} == date.day());
}

TEST(Date, handles_valid_and_invalid_dates)
{
    static_assert(Date{Year{2019}, Month{2}, Day{1}}.valid());
    static_assert(Date{Year{2019}, Month{2}, Day{28}}.valid());

    static_assert(!Date{Year{2019}, Month{2}, Day{29}}.valid());
    static_assert(!Date{Year{2019}, Month{13}, Day{22}}.valid());
}

TEST(Date, adds_days)
{
    constexpr Date date{Year{2016}, Month{1}, Day{31}};
    constexpr Date expected{Year{2016}, Month{3}, Day{1}};

    constexpr Date modified{date + Days{30}};

    static_assert(expected == modified);
}

TEST(Date, adds_many_days)
{
    constexpr Date date{Year{2016}, Month{2}, Day{20}};
    constexpr Date expected{Year{2017}, Month{9}, Day{5}};

    constexpr Date modified{date + Days{563}};

    static_assert(expected == modified);
}

TEST(Date, subtracts_days)
{
    constexpr Date date{Year{2016}, Month{2}, Day{29}};
    constexpr Date expected{Year{2016}, Month{2}, Day{20}};

    constexpr Date modified{date - Days{9}};

    static_assert(expected == modified);
}

TEST(Date, subtracts_many_days)
{
    constexpr Date date{Year{2017}, Month{9}, Day{5}};
    constexpr Date expected{Year{2016}, Month{2}, Day{20}};

    constexpr Date modified{date - Days{563}};

    static_assert(expected == modified);
}

TEST(Date, adds_weeks)
{
    constexpr Date date{Year{2018}, Month{12}, Day{28}};
    constexpr Date expected{Year{2019}, Month{1}, Day{18}};

    constexpr Date modified{date + Weeks{3}};

    static_assert(expected == modified);
}

TEST(Date, subtracts_weeks)
{
    constexpr Date date{Year{2019}, Month{1}, Day{18}};
    constexpr Date expected{Year{2018}, Month{12}, Day{28}};

    constexpr Date modified{date - Weeks{3}};

    static_assert(expected == modified);
}

TEST(Date, adds_months)
{
    constexpr Date date{Year{2016}, Month{2}, Day{20}};
    constexpr Date expected{Year{2017}, Month{7}, Day{20}};

    constexpr Date modified{date + Months{17}};

    static_assert(expected == modified);
}

TEST(Date, adding_months_sets_date_to_latest_valid_when_day_field_overflows)
{
    constexpr Date date{Year{2016}, Month{8}, Day{31}};
    constexpr Date expected{Year{2016}, Month{9}, Day{30}};

    constexpr Date modified{date + Months{1}};

    static_assert(expected == modified);
}

TEST(Date, subtracts_months)
{
    constexpr Date date{Year{2017}, Month{7}, Day{20}};
    constexpr Date expected{Year{2016}, Month{2}, Day{20}};

    constexpr Date modified{date - Months{17}};

    static_assert(expected == modified);
}

TEST(Date, subtract_months_sets_date_to_latest_valid_when_day_field_overflows)
{
    constexpr Date date{Year{2019}, Month{3}, Day{31}};
    constexpr Date expected{Year{2019}, Month{2}, Day{28}};

    constexpr Date modified{date - Months{1}};

    static_assert(expected == modified);
}

TEST(Date, normalizes_invalid_date)
{
    static_assert(Date{Year{2020}, Month{3}, Day{6}}
                  == normalize(Date{Year{2015}, Month{55}, Day{250}}));
}

TEST(Date, adds_years)
{
    constexpr Date date{Year{2016}, Month{3}, Day{10}};
    constexpr Date expected{Year{12016}, Month{3}, Day{10}};

    constexpr Date modified{date + Years{10000}};

    static_assert(expected == modified);
}

TEST(Date, adding_years_sets_date_to_latest_valid_when_day_field_overflows)
{
    constexpr Date date{Year{2016}, Month{2}, Day{29}};
    constexpr Date expected_invalid{Year{2017}, Month{2}, Day{28}};

    constexpr Date modified_invalid{date + Years{1}};

    static_assert(expected_invalid == modified_invalid);
}

TEST(Date, subtracts_years)
{
    constexpr Date date{Year{20117}, Month{2}, Day{28}};
    constexpr Date expected{Year{1956}, Month{2}, Day{28}};

    constexpr Date modified{date - Years{18161}};

    static_assert(expected == modified);
}

TEST(Date, subtracting_years_sets_date_to_latest_valid_when_day_field_overflows)
{
    constexpr Date date{Year{2016}, Month{2}, Day{29}};
    constexpr Date expected{Year{2015}, Month{2}, Day{28}};

    constexpr Date modified{date - Years{1}};

    static_assert(expected == modified);
}

TEST(Date, returns_weekday)
{
    constexpr Date monday{Year{2016}, Month{4}, Day{4}};
    constexpr Date tuesday{Year{2016}, Month{4}, Day{5}};
    constexpr Date wednesday{Year{2016}, Month{4}, Day{6}};
    constexpr Date thursday{Year{2016}, Month{4}, Day{7}};
    constexpr Date friday{Year{2016}, Month{4}, Day{8}};
    constexpr Date saturday{Year{2016}, Month{4}, Day{9}};
    constexpr Date sunday{Year{2016}, Month{4}, Day{10}};

    static_assert(Weekday::Monday == weekday(monday));
    static_assert(Weekday::Tuesday == weekday(tuesday));
    static_assert(Weekday::Wednesday == weekday(wednesday));
    static_assert(Weekday::Thursday == weekday(thursday));
    static_assert(Weekday::Friday == weekday(friday));
    static_assert(Weekday::Saturday == weekday(saturday));
    static_assert(Weekday::Sunday == weekday(sunday));
}

TEST(Date, ostream_operator)
{
    const Date date{Year{2019}, Month{8}, Day{7}};
    const std::string expected{"07.08.2019"};
    std::stringstream ss;

    ss << date;

    EXPECT_EQ(expected, ss.str());
}

TEST(Date, to_string_handles_valid_date_format)
{
    const Date date{Year{2016}, Month{9}, Day{21}};

    EXPECT_EQ("2016.09.21", to_string(date, "yyyy.MM.dd"));
    EXPECT_EQ("201616", to_string(date, "yyyyyy"));
    EXPECT_EQ("21", to_string(date, "d"));
    EXPECT_EQ("2121", to_string(date, "ddd"));
    EXPECT_EQ("9", to_string(date, "M"));
    EXPECT_EQ("099", to_string(date, "MMM"));
}

TEST(Date, to_string_ignores_single_quote_that_has_no_pair)
{
    const Date date{Year{2016}, Month{9}, Day{21}};

    EXPECT_EQ("21-09-2016", to_string(date, "dd-'MM-yyyy"));
}

TEST(Date, to_string_threats_input_in_single_quotes_as_text)
{
    const Date date{Year{2016}, Month{9}, Day{21}};

    EXPECT_EQ("2016|what|09ahhMM21",
              to_string(date, "yyyy|'what'|MM'ahhMM'dd"));
}

TEST(Date, to_string_double_single_quotes_replaced_by_single_quote_in_output)
{
    const Date date{Year{2016}, Month{9}, Day{21}};

    EXPECT_EQ("2016'09'21", to_string(date, "yyyy''MM''dd"));
}

TEST(Date, returns_previous_weekday)
{
    constexpr Date monday{Year{2019}, Month{2}, Day{25}};
    constexpr Date friday{Year{2019}, Month{3}, Day{1}};
    constexpr Date sunday{Year{2019}, Month{3}, Day{3}};

    static_assert(monday == prev_weekday(monday, Weekday::Monday));
    static_assert(monday == prev_weekday(sunday, Weekday::Monday));
    static_assert(friday == prev_weekday(sunday, Weekday::Friday));
}

TEST(Date, returns_next_weekday)
{
    constexpr Date monday{Year{2019}, Month{2}, Day{25}};
    constexpr Date tuesday{Year{2019}, Month{2}, Day{26}};
    constexpr Date thursday{Year{2019}, Month{2}, Day{28}};
    constexpr Date sunday{Year{2019}, Month{3}, Day{3}};

    static_assert(sunday == next_weekday(monday, Weekday::Sunday));
    static_assert(sunday == next_weekday(sunday, Weekday::Sunday));
    static_assert(thursday == next_weekday(tuesday, Weekday::Thursday));
}

TEST(Date, returns_previous_weekday_excluding_current)
{
    constexpr Date prev_sunday{Year{2019}, Month{2}, Day{24}};
    constexpr Date monday{Year{2019}, Month{2}, Day{25}};
    constexpr Date sunday{Year{2019}, Month{3}, Day{3}};

    static_assert(prev_sunday
                  == prev_weekday_excluding_current(sunday, Weekday::Sunday));
    static_assert(monday
                  == prev_weekday_excluding_current(sunday, Weekday::Monday));
}

TEST(Date, returns_next_weekday_excluding_current)
{
    constexpr Date monday{Year{2019}, Month{2}, Day{25}};
    constexpr Date sunday{Year{2019}, Month{3}, Day{3}};
    constexpr Date next_monday{Year{2019}, Month{3}, Day{4}};

    static_assert(next_monday
                  == next_weekday_excluding_current(monday, Weekday::Monday));
    static_assert(sunday
                  == next_weekday_excluding_current(monday, Weekday::Sunday));
}

TEST(Date, returns_last_day_of_month)
{
    constexpr Date firstDay{Year{2019}, Month{2}, Day{1}};
    constexpr Date lastDay{Year{2019}, Month{2}, Day{28}};

    static_assert(lastDay == last_day_of_month(firstDay));
    static_assert(lastDay == last_day_of_month(lastDay));
}

TEST(Date, comparison_operators_different_days)
{
    constexpr Date before{Year{2018}, Month{11}, Day{16}};
    constexpr Date date{Year{2018}, Month{11}, Day{17}};
    constexpr Date after{Year{2018}, Month{11}, Day{18}};

    static_assert(date == date);
    static_assert(date <= after);
    static_assert(date >= before);
    static_assert(before <= date);
    static_assert(before < date);
    static_assert(after >= date);
    static_assert(after > date);
}

TEST(Date, comparison_operators_different_months)
{
    constexpr Date before{Year{2018}, Month{10}, Day{17}};
    constexpr Date date{Year{2018}, Month{11}, Day{17}};
    constexpr Date after{Year{2018}, Month{12}, Day{17}};

    static_assert(date == date);
    static_assert(date <= after);
    static_assert(date >= before);
    static_assert(before <= date);
    static_assert(before < date);
    static_assert(after >= date);
    static_assert(after > date);
}

TEST(Date, comparison_operators_different_years)
{
    constexpr Date before{Year{2017}, Month{11}, Day{17}};
    constexpr Date date{Year{2018}, Month{11}, Day{17}};
    constexpr Date after{Year{2019}, Month{11}, Day{17}};

    static_assert(date == date);
    static_assert(date <= after);
    static_assert(date >= before);
    static_assert(before <= date);
    static_assert(before < date);
    static_assert(after >= date);
    static_assert(after > date);
}

TEST(Date, converts_to_sys_days)
{
    constexpr Date date{Year{2018}, Month{11}, Day{17}};
    constexpr date::sys_days expected{
        date::year_month_day{date::year{2018}, date::month{11}, date::day{17}}};

    static_assert(expected == sys_days(date));
}
