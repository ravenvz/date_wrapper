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
#ifndef DATE_H_AF2T5LBF
#define DATE_H_AF2T5LBF

#ifdef __linux__
#include <time.h>
#endif

#include <date/date.h>
#include <iomanip>

#include <iostream>

using Days = date::days;
using Weeks = date::weeks;
using Months = date::months;
using Years = date::years;

namespace utils {

constexpr std::array<unsigned, 7> mondayFirstTable{
    {6u, 0u, 1u, 2u, 3u, 4u, 5u}};

constexpr std::array<unsigned, 7> sundayFirstTable{
    {1u, 2u, 3u, 4u, 5u, 6u, 0u}};

constexpr date::year_month_day normalize(date::year_month_day ymd) noexcept;

bool startsWith(std::string_view str, std::string_view prefix);

bool startsWith(std::string_view str, char ch);

} // namespace utils

namespace dw {

enum class Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};


struct Year {
    explicit constexpr Year(int year) noexcept;

    constexpr int value() const noexcept;

    explicit constexpr operator int() const noexcept;

private:
    date::year year_;
};


struct Month {
    explicit constexpr Month(unsigned month) noexcept;

    constexpr unsigned value() const noexcept;

private:
    date::month month_;
};


struct Day {
    explicit constexpr Day(unsigned day) noexcept;

    constexpr unsigned value() const noexcept;

private:
    date::day day_;
};


class Date {
public:
    constexpr Date(Year year, Month month, Day day) noexcept;

    constexpr Year year() const noexcept;

    constexpr Month month() const noexcept;

    constexpr Day day() const noexcept;

    constexpr bool valid() const noexcept;

    constexpr Weekday weekday() const noexcept;

    /* Returns first Date before current Date that has target Weekday
     * or the same Date if it already has the target Weekday. */
    constexpr Date prev_weekday(Weekday target) const noexcept;

    /* Returns first Date before current Date that has target Weekday,
     * even if current date already has target Weekday. */
    constexpr Date prev_weekday_excluding_current(Weekday target) const
        noexcept;

    /* Returns first Date after current Date that has target Weekday or
     * the same Date if it already has the target Weekday. */
    constexpr Date next_weekday(Weekday target) const noexcept;

    /* Returns first Date after current Date that has target Weekday,
     * even if current date already has target Weekday. */
    constexpr Date next_weekday_excluding_current(Weekday target) const
        noexcept;

    /* Returns Date that corresponds to the last day of month for the current
     * Date. */
    constexpr Date last_day_of_month() const noexcept;

    /* Returns new Date with number of days added (or subtructed) to given date.
     */
    friend constexpr Date operator+(const Date& date,
                                    const Days& days) noexcept;
    friend constexpr Date operator-(const Date& date,
                                    const Days& days) noexcept;

    friend constexpr Date operator+(const Date& date,
                                    const Weeks& weeks) noexcept;

    friend constexpr Date operator-(const Date& date,
                                    const Weeks& weeks) noexcept;

    /* Returns new Date with number of months added to it.
     *
     * Adding month is a bit ambiguous operation when considering day number.
     * This version tries to preserve day number, but in corner cases day is set
     * to the last day of month, i.e.:
     *
     *  31.8.2017 + 1 month => 30.9.2017 but 30.9.2017 - 1 month => 30.8.2017
     *  30.3.2019 - 1 month => 28.2.2019 but 28.2.2018 + 1 month => 28.3.2019
     *
     *  */
    friend constexpr Date operator+(const Date& date,
                                    const Months& months) noexcept;
    friend constexpr Date operator-(const Date& date,
                                    const Months& months) noexcept;

    friend constexpr Date operator+(const Date& date,
                                    const Years& years) noexcept;
    friend constexpr Date operator-(const Date& date,
                                    const Years& years) noexcept;


private:
    date::year_month_day ymd_;

    explicit constexpr Date(date::year_month_day&& ymd) noexcept;

    explicit constexpr Date(date::sys_days&& days) noexcept;
};

/* Returns current date UTC */
Date current_date() noexcept;

/* Returns current date for local time zone.
 * NOTE: Not thread-safe */
Date current_date_local() noexcept;

/* Return string representation of Date.
 * The format parameter determines the format of the result string.
 *
 * These expressions may be used for the date:
 *
 * d	the day as number without a leading zero (1 to 31)
 * dd	the day as number with a leading zero (01 to 31)
 * M	the month as number without a leading zero (1-12)
 * MM	the month as number with a leading zero (01-12)
 * yy	the year as two digit number (00-99)
 * yyyy	the year as four digit number
 *
 * All other input characters will be ignored.
 * Any sequence of characters that are enclosed in single quotes will be
 * treated as text and not be used as an expression.
 */
std::string to_string(const Date& date, std::string_view format);

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Date& date);

constexpr bool operator==(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator!=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator<=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator<(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator>=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator>(const Date& lhs, const Date& rhs) noexcept;

constexpr Year::Year(int year) noexcept
    : year_{year}
{
}

constexpr int Year::value() const noexcept { return int{year_}; }

constexpr Year::operator int() const noexcept { return int{year_}; }


constexpr Month::Month(unsigned month) noexcept
    : month_{static_cast<decltype(month_)>(month)}
{
}

constexpr unsigned Month::value() const noexcept
{
    return static_cast<unsigned>(month_);
}


constexpr Day::Day(unsigned day) noexcept
    : day_{static_cast<decltype(day_)>(day)}
{
}

constexpr unsigned Day::value() const noexcept
{
    return static_cast<unsigned>(day_);
}

constexpr Date::Date(Year year, Month month, Day day) noexcept
    : ymd_{date::year{year.value()},
           date::month{month.value()},
           date::day{day.value()}}
{
}

constexpr Date::Date(date::year_month_day&& ymd) noexcept
    : ymd_{ymd}
{
}

constexpr Date::Date(date::sys_days&& days) noexcept
    : ymd_{days}
{
}

constexpr Year Date::year() const noexcept
{
    return Year{static_cast<int>(ymd_.year())};
}

constexpr Month Date::month() const noexcept
{
    return Month{static_cast<unsigned>(ymd_.month())};
}

constexpr Day Date::day() const noexcept
{
    return Day{static_cast<unsigned>(ymd_.day())};
}

constexpr bool Date::valid() const noexcept { return ymd_.ok(); }

constexpr Weekday Date::weekday() const noexcept
{
    return static_cast<Weekday>(
        utils::mondayFirstTable[static_cast<unsigned>(date::weekday(ymd_))]);
}

constexpr Date Date::prev_weekday(Weekday target) const noexcept
{
    const date::sys_days sd{ymd_};
    const date::weekday target_weekday{
        utils::sundayFirstTable[static_cast<unsigned>(target)]};
    return Date{
        date::year_month_day{sd - (date::weekday{sd} - target_weekday)}};
}

constexpr Date Date::prev_weekday_excluding_current(Weekday target) const
    noexcept
{
    return (*this - Days{1}).prev_weekday(target);
}

constexpr Date Date::next_weekday(Weekday target) const noexcept
{
    const date::sys_days sd{ymd_};
    const date::weekday target_weekday{
        utils::sundayFirstTable[static_cast<unsigned>(target)]};
    return Date{
        date::year_month_day{sd + (target_weekday - date::weekday{sd})}};
}

constexpr Date Date::next_weekday_excluding_current(Weekday target) const
    noexcept
{
    return (*this + Days{1}).next_weekday(target);
}

constexpr Date Date::last_day_of_month() const noexcept
{
    return Date{date::year_month_day{ymd_.year() / ymd_.month() / date::last}};
}

inline Date current_date() noexcept
{
    auto timepoint = std::chrono::system_clock::now();
    date::year_month_day ymd{std::chrono::floor<date::days>(timepoint)};
    return Date{Year{static_cast<int>(ymd.year())},
                Month{static_cast<unsigned>(ymd.month())},
                Day{static_cast<unsigned>(ymd.day())}};
}

inline Date current_date_local() noexcept
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(timepoint);
#ifdef __linux__
    std::tm local_time;
    localtime_r(&t, &local_time);
#else
    std::tm local_time = *std::localtime(&t);
#endif
    return Date{Year{local_time.tm_year + 1900},
                Month{static_cast<unsigned>(local_time.tm_mon + 1)},
                Day{static_cast<unsigned>(local_time.tm_mday)}};
}

inline std::string to_string(const Date& date, std::string_view format)
{
    using namespace utils;
    std::stringstream ss;

    while (!format.empty()) {
        if (startsWith(format, "''")) {
            ss << '\'';
            format.remove_prefix(2);
        }
        else if (startsWith(format, '\'')) {
            format.remove_prefix(1);
            if (format.find_first_of('\'') != std::string_view::npos) {
                while (!startsWith(format, '\'')) {
                    ss << format.front();
                    format.remove_prefix(1);
                }
                format.remove_prefix(1);
            }
        }
        else if (startsWith(format, "yyyy")) {
            ss << std::setfill('0') << std::setw(4) << date.year().value();
            format.remove_prefix(4);
        }
        else if (startsWith(format, "yy")) {
            ss << std::setfill('0') << std::setw(2)
               << date.year().value() % 100;
            format.remove_prefix(2);
        }
        else if (startsWith(format, "MM")) {
            ss << std::setfill('0') << std::setw(2) << date.month().value();
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'M')) {
            ss << date.month().value();
            format.remove_prefix(1);
        }
        else if (startsWith(format, "dd")) {
            ss << std::setfill('0') << std::setw(2) << date.day().value();
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'd')) {
            ss << date.day().value();
            format.remove_prefix(1);
        }
        else {
            ss << format.front();
            format.remove_prefix(1);
        }
    }

    return ss.str();
}

inline constexpr Date operator+(const Date& date, const Days& days) noexcept
{
    return Date{date::sys_days(date.ymd_) + days};
}

inline constexpr Date operator-(const Date& date, const Days& days) noexcept
{
    return Date{date::sys_days(date.ymd_) - days};
}

inline constexpr Date operator+(const Date& date, const Weeks& weeks) noexcept
{
    return date + Days{weeks.count() * 7};
}

inline constexpr Date operator-(const Date& date, const Weeks& weeks) noexcept
{
    return date - Days{weeks.count() * 7};
}

inline constexpr Date operator+(const Date& date, const Months& months) noexcept
{
    return Date{utils::normalize(date.ymd_ + date::months{months.count()})};
}

inline constexpr Date operator-(const Date& date, const Months& months) noexcept
{
    return Date{utils::normalize(date.ymd_ - date::months{months.count()})};
}

inline constexpr Date operator+(const Date& date, const Years& years) noexcept
{
    return Date{utils::normalize(date.ymd_ + date::years{years.count()})};
}

inline constexpr Date operator-(const Date& date, const Years& years) noexcept
{
    return Date{utils::normalize(date.ymd_ - date::years{years.count()})};
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Date& date)
{
    os << std::setfill('0') << std::setw(2) << date.day().value() << '.'
       << std::setfill('0') << std::setw(2) << date.month().value() << '.'
       << date.year().value();
    return os;
}

inline constexpr bool operator==(const Date& lhs, const Date& rhs) noexcept
{
    return lhs.year().value() == rhs.year().value()
        && lhs.month().value() == rhs.month().value()
        && lhs.day().value() == rhs.day().value();
}

constexpr bool operator!=(const Date& lhs, const Date& rhs) noexcept
{
    return !(lhs == rhs);
}

constexpr bool operator<=(const Date& lhs, const Date& rhs) noexcept
{
    return !(lhs > rhs);
}

constexpr bool operator<(const Date& lhs, const Date& rhs) noexcept
{
    return lhs.year().value() < rhs.year().value()
        ? true
        : (lhs.year().value() > rhs.year().value()
               ? false
               : (lhs.month().value() < rhs.month().value()
                      ? true
                      : (lhs.month().value() > rhs.month().value()
                             ? false
                             : (lhs.day().value() < rhs.day().value()))));
}

constexpr bool operator>=(const Date& lhs, const Date& rhs) noexcept
{
    return !(lhs < rhs);
}

constexpr bool operator>(const Date& lhs, const Date& rhs) noexcept
{
    return rhs < lhs;
}

} // namespace dw

namespace utils {

inline constexpr date::year_month_day
normalize(date::year_month_day ymd) noexcept
{
    using namespace date;
    if (!ymd.ok())
        return ymd.year() / ymd.month() / last;
    return ymd;
}

inline bool startsWith(std::string_view str, std::string_view prefix)
{
    if (prefix.size() > str.size())
        return false;
    return std::equal(prefix.cbegin(), prefix.cend(), str.cbegin());
}

inline bool startsWith(std::string_view str, char ch)
{
    return !str.empty() && str[0] == ch;
}

inline constexpr date::weekday convert(dw::Weekday weekday) noexcept
{
    return date::weekday{sundayFirstTable[static_cast<unsigned>(weekday) + 1]};
}

} // namespace utils

#endif /* end of include guard: DATE_H_AF2T5LBF */
