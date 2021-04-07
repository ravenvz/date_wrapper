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
#ifndef DATE_WRAPPER_H_XU053LKE
#define DATE_WRAPPER_H_XU053LKE

#ifdef __linux__
#include <time.h>
#endif

#include <date/date.h>
#include <date/iso_week.h>
#include <iomanip>

namespace dw {

using Days = date::days;
using Weeks = date::weeks;
using Months = date::months;
using Years = date::years;
using sys_days = date::sys_days;

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

    explicit constexpr operator int() const noexcept;

private:
    date::year year_;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Year& year);

constexpr bool operator==(const Year& lhs, const Year& rhs) noexcept;

constexpr bool operator!=(const Year& lhs, const Year& rhs) noexcept;

struct Month {
    explicit constexpr Month(unsigned month) noexcept;

    explicit constexpr operator unsigned() const noexcept;

private:
    date::month month_;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Month& month);

constexpr bool operator==(const Month& lhs, const Month& rhs) noexcept;

constexpr bool operator!=(const Month& lhs, const Month& rhs) noexcept;

struct Day {
    explicit constexpr Day(unsigned day) noexcept;

    explicit constexpr operator unsigned() const noexcept;

private:
    date::day day_;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Day& day);

constexpr bool operator==(const Day& lhs, const Day& rhs) noexcept;

constexpr bool operator!=(const Day& lhs, const Day& rhs) noexcept;

class Date {
public:
    constexpr Date(Year year, Month month, Day day) noexcept;

    constexpr Year year() const noexcept;

    constexpr Month month() const noexcept;

    constexpr Day day() const noexcept;

    constexpr bool valid() const noexcept;

    constexpr operator sys_days() const noexcept;

private:
    date::year_month_day ymd_;
};

constexpr Weekday weekday(const Date& date) noexcept;

/* Returns first Date before current Date that has target Weekday
 * or the same Date if it already has the target Weekday. */
constexpr Date prev_weekday(const Date& date, Weekday target) noexcept;

/* Returns first Date before current Date that has target Weekday,
 * even if current date already has target Weekday. */
constexpr Date prev_weekday_excluding_current(const Date& date,
                                              Weekday target) noexcept;

/* Returns first Date after current Date that has target Weekday or
 * the same Date if it already has the target Weekday. */
constexpr Date next_weekday(const Date& date, Weekday target) noexcept;

/* Returns first Date after current Date that has target Weekday,
 * even if current date already has target Weekday. */
constexpr Date next_weekday_excluding_current(const Date& date,
                                              Weekday target) noexcept;

/* Returns Date that corresponds to the last day of month for the current
 * Date. */
constexpr Date last_day_of_month(const Date& date) noexcept;

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

/* Returns new Date with days.count() days added to it. */
constexpr Date operator+(const Date& date, const Days& days) noexcept;

/* Returns new Date with days.count() subracted from it.
 * Equivalent to date + -days. */
constexpr Date operator-(const Date& date, const Days& days) noexcept;

/* Returns new Date with 7 * weeks.count() days added to it. */
constexpr Date operator+(const Date& date, const Weeks& weeks) noexcept;

/* Returns new Date with 7 * weeks.count() days subtracted from it.
 * Equivalent to date + -weeks. */
constexpr Date operator-(const Date& date, const Weeks& weeks) noexcept;

/* Returns new Date with months.count() added to it. The result has the
 * same day number as original date. Note that resulting date might not
 * represent a valid date if date.day() is 29, 30 or 31. In that case the
 * latest valid date is returned. */
constexpr Date operator+(const Date& date, const Months& months) noexcept;

/* Returns new Date with months.count() subtracted from it. The result has the
 * same day number as original date. Note that resulting date might not
 * represent a valid date if date.day() is 29, 30 or 31. In that case the latest
 * valid date is returned.
 *
 * Equivalent to date + -months. */
constexpr Date operator-(const Date& date, const Months& months) noexcept;

/* Returns new Date with years.count() added to it. The result has the
 * same month and day number as original date. Note that resulting date might
 * not represent a valid date if date.day() is 29, 30 or 31. In that case the
 * latest valid date is returned. */
constexpr Date operator+(const Date& date, const Years& years) noexcept;

/* Returns new Date with years.count() subtracted from it. The result has the
 * same month and day number as original date. Note that resulting date might
 * not represent a valid date if date.day() is 29, 30 or 31. In that case the
 * latest valid date is returned.
 *
 * Equivalent to date + -years. */
constexpr Date operator-(const Date& date, const Years& years) noexcept;

/* Returns "normalized" date when date is invalid, otherwise returns the same
 date.
 *
 * Date is "normalized" as follows:
 * If date.month() is 0, this will subtract one from the year and set the month
 * to Dec. If date.month() is greater than 12, the year will be incremented as
 many
 * times as appropriate, and the month will be brought within the proper range.
 * After month is "normalized" day field is brought withing the proper range:
 * i.e. 2015.12.32 becomes 2016.01.01
 *
 * This function can be used to 'normalize' any invalid Date, i.e.
 * 2015.55.250 becomes 2020.03.06.
 */
constexpr Date normalize(const Date& date) noexcept;

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Date& date);

constexpr bool operator==(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator!=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator<=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator<(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator>=(const Date& lhs, const Date& rhs) noexcept;

constexpr bool operator>(const Date& lhs, const Date& rhs) noexcept;

/* Immutable datatype that stores date and time. */
class DateTime {
public:
    using precision = std::chrono::system_clock::duration;

    template <typename Clock, typename Duration>
    constexpr explicit DateTime(
        const std::chrono::time_point<Clock, Duration>& timepoint) noexcept;

    constexpr explicit DateTime(const Date& date) noexcept;

    template <typename Rep, typename Period>
    constexpr DateTime(
        const Date& date,
        const std::chrono::duration<Rep, Period>& time_since_midnight) noexcept;

    constexpr Date date() const noexcept;

    constexpr Year year() const noexcept;

    constexpr Month month() const noexcept;

    constexpr Day day() const noexcept;

    constexpr precision time() const noexcept;

    /* Return hours since midnight in 24-h format. */
    constexpr std::chrono::hours hour() const noexcept;

    /* Return minutes since the start of the hour. */
    constexpr std::chrono::minutes minute() const noexcept;

    /* Return seconds since the start of the minute. */
    constexpr std::chrono::seconds second() const noexcept;

    /* Return day of week. */
    constexpr Weekday weekday() const noexcept;

private:
    date::year_month_day ymd;
    date::time_of_day<std::chrono::system_clock::duration> tod;
};

/* Returns current DateTime using std::chrono::system_clock. */
DateTime current_date_time() noexcept;

/* Note: might not be thread-safe. */
DateTime current_date_time_local() noexcept;

/* Returns time point with specified resolution.
 *
 * Note, that using coarse resolution will lead to truncation loss.
 *
 * Also note, that when dealing with very fine resolution or very large date,
 * special care needs to be taken, as these cases are subject to
 * potential overflow error; in other words, user must be sure that requested
 * duration is able to hold the desired value.
 */
template <typename ToDuration,
          typename Clock = std::chrono::system_clock,
          typename Duration = typename Clock::duration>
constexpr std::chrono::time_point<Clock, ToDuration>
to_time_point(const DateTime& dt) noexcept;

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateTime& dt);

/* Return string representation of DateTime.
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
 * These expressions may be used for the time:
 *
 * h	the hour without a leading zero (0 to 23 or 1 to 12 if AM/PM
 * display)
 * hh	the hour with a leading zero (00 to 23 or 01 to 12 if AM/PM
 * display)
 * m	the minute without a leading zero (0 to 59)
 * mm	the minute with a leading zero (00 to 59)
 * s	the second without a leading zero (0 to 59)
 * ss	the second with a leading zero (00 to 59)
 *
 * All other input characters will be ignored.
 * Any sequence of characters that are enclosed in single quotes will be
 * treated as text and not be used as an expression.
 */
std::string to_string(const DateTime& dt, std::string_view format);

constexpr bool operator==(const DateTime& lhs, const DateTime& rhs) noexcept;

constexpr bool operator!=(const DateTime& lhs, const DateTime& rhs) noexcept;

constexpr bool operator<(const DateTime& lhs, const DateTime& rhs) noexcept;

constexpr bool operator<=(const DateTime& lhs, const DateTime& rhs) noexcept;

constexpr bool operator>(const DateTime& lhs, const DateTime& rhs) noexcept;

constexpr bool operator>=(const DateTime& lhs, const DateTime& rhs) noexcept;

/* Return new DateTime object that stands apart in time by given duration.
 *
 * Note that there are two ways to deal with date and time computations -
 * chronological and calendrical.
 * Chronological computation deals with regular time intervals (say, hours,
 * days, average month length) while calendrical computation tries to
 * preserve time of day and day of month when modifying date and time.
 *
 * This operator performes calendric computations.
 *
 * In case when adding duration will result in invalid date, DateTime that
 * has the latest valid date will be returned,
 * i.e. (31.02.2019) -> * (28.02.2019).
 */
template <typename Rep, typename Period>
constexpr DateTime
operator+(const DateTime& dt,
          const std::chrono::duration<Rep, Period>& duration) noexcept;

template <typename Rep, typename Period>
constexpr DateTime
operator-(const DateTime& dt,
          const std::chrono::duration<Rep, Period>& duration) noexcept;

constexpr DateTime operator+(const DateTime& dt, const Months& months) noexcept;

constexpr DateTime operator-(const DateTime& dt, const Months& months) noexcept;

constexpr DateTime operator+(const DateTime& dt, const Years& years) noexcept;

constexpr DateTime operator-(const DateTime& dt, const Years& years) noexcept;

class IsoDate {
public:
    template <typename Clock, typename Duration>
    constexpr IsoDate(
        const std::chrono::time_point<Clock, Duration>& time_point);

    constexpr IsoDate(const DateTime& dt);

    constexpr IsoDate(const Date& date);

    constexpr unsigned weeknum() const noexcept;

    constexpr Year year() const noexcept;

    constexpr Weekday weekday() const noexcept;

    friend constexpr bool operator==(const IsoDate& lhs,
                                     const IsoDate& rhs) noexcept;

private:
    const iso_week::year_weeknum_weekday i_week;
};

/* Represent finite interval of dates. */
class DateRange {
public:
    constexpr DateRange(Date start, Date finish) noexcept;

    constexpr Date start() const noexcept;

    constexpr Date finish() const noexcept;

    /* Returns duration in Days (that is std::chrono::duration type). */
    constexpr Days duration() const noexcept;

private:
    Date start_;
    Date finish_;
};

constexpr bool operator==(const DateRange& lhs, const DateRange& rhs);

constexpr bool operator!=(const DateRange& lhs, const DateRange& rhs);

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateRange& ds);

/* Returns new DateRange with start and finish adjusted by offset. */
constexpr DateRange add_offset(const DateRange& date_range,
                               const Days& offset) noexcept;

std::string to_string(const DateRange& ds,
                      std::string_view format,
                      std::string sep = " - ");

/* Represent finite interval in time with start and finish points. */
struct DateTimeRange {

    template <typename Clock, typename Duration>
    constexpr DateTimeRange(
        const std::chrono::time_point<Clock, Duration>& start,
        const std::chrono::time_point<Clock, Duration>& finish) noexcept;

    constexpr DateTimeRange(const DateTime& start,
                            const DateTime& finish) noexcept;

    constexpr DateTime start() const noexcept;

    constexpr DateTime finish() const noexcept;

    /* Return size of TimeInterval with specified duration.
     * Duration is restricted to std::chrono::duration type.
     * Note, that when dealing with very fine resolution or very large date
     * range, special care needs to be taken, as these cases are subject
     * to potential overflow error; in other words, user must be sure that
     * requested duration is able to hold the desired value.
     */
    template <typename ToDuration>
    constexpr ToDuration duration() const noexcept;

private:
    DateTime start_;
    DateTime finish_;
};

/* Return string representation of DateTimeRange. The result is determined
 * by format string that is applied both to start and finish DateTime
 * objects, separated by sep string.
 * See also documentation for to_string(const DateTime& ...) for format
 * specification.
 */
std::string to_string(const DateTimeRange& date_time_range,
                      std::string_view format,
                      std::string sep = " - ");

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateTimeRange& span);

constexpr bool operator!=(const DateTimeRange& lhs,
                          const DateTimeRange& rhs) noexcept;

constexpr bool operator==(const DateTimeRange& lhs,
                          const DateTimeRange& rhs) noexcept;

/* Returns new DateTimeRange with start and finish adjusted by offset. */
constexpr DateTimeRange add_offset(const DateTimeRange& dt_range,
                                   std::chrono::seconds offset) noexcept;

namespace utils {

bool startsWith(std::string_view str, std::string_view prefix);

bool startsWith(std::string_view str, char ch);

constexpr date::weekday convert(dw::Weekday weekday) noexcept;

/* Convert std::tm to std::chrono::timepoint. */
template <typename Clock, typename Duration>
void fill_timepoint(const std::tm& t,
                    std::chrono::time_point<Clock, Duration>& tp);

template <typename T> struct is_chrono_duration {
    static constexpr bool value = false;
};

template <typename Rep, typename Period>
struct is_chrono_duration<std::chrono::duration<Rep, Period>> {
    static constexpr bool value = true;
};

std::string formatDateTime(const DateTime& dt, std::string_view format);

constexpr Date from_ymd(const date::year_month_day& ymd) noexcept;

constexpr date::year_month_day to_ymd(const Date& date) noexcept;

} // namespace utils

// Year implementation

constexpr Year::Year(int year) noexcept
    : year_{year}
{
}

constexpr Year::operator int() const noexcept
{
    return static_cast<int>(year_);
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Year& year)
{
    os << "Year{" << static_cast<int>(year);
    return os;
}

constexpr bool operator==(const Year& lhs, const Year& rhs) noexcept
{
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}

constexpr bool operator!=(const Year& lhs, const Year& rhs) noexcept
{
    return !(lhs == rhs);
}

// Month implementation

constexpr Month::Month(unsigned month) noexcept
    : month_{static_cast<decltype(month_)>(month)}
{
}

constexpr Month::operator unsigned() const noexcept
{
    return static_cast<unsigned>(month_);
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Month& month)
{
    os << "Month{" << static_cast<unsigned>(month) << "}";
    return os;
}

constexpr bool operator==(const Month& lhs, const Month& rhs) noexcept
{
    return static_cast<unsigned>(lhs) == static_cast<unsigned>(rhs);
}

constexpr bool operator!=(const Month& lhs, const Month& rhs) noexcept
{
    return !(lhs == rhs);
}

// Day implementation

constexpr Day::Day(unsigned day) noexcept
    : day_{static_cast<decltype(day_)>(day)}
{
}

constexpr Day::operator unsigned() const noexcept
{
    return static_cast<unsigned>(day_);
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Day& day)
{
    os << "Day{" << static_cast<unsigned>(day) << "}";
    return os;
}

constexpr bool operator==(const Day& lhs, const Day& rhs) noexcept
{
    return static_cast<unsigned>(lhs) == static_cast<unsigned>(rhs);
}

constexpr bool operator!=(const Day& lhs, const Day& rhs) noexcept
{
    return !(lhs == rhs);
}

// Date implementation

constexpr Date::Date(Year year, Month month, Day day) noexcept
    : ymd_{date::year{static_cast<int>(year)},
           date::month{static_cast<unsigned>(month)},
           date::day{static_cast<unsigned>(day)}}
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

constexpr Date::operator sys_days() const noexcept { return ymd_; }

constexpr Date prev_weekday(const Date& date, Weekday target) noexcept
{
    const date::sys_days sd{utils::to_ymd(date)};
    const date::weekday target_weekday{static_cast<unsigned>(target) + 1};
    return Date{utils::from_ymd(
        date::year_month_day{sd - (date::weekday{sd} - target_weekday)})};
}

constexpr Date prev_weekday_excluding_current(const Date& date,
                                              Weekday target) noexcept
{
    return prev_weekday(date - Days{1}, target);
}

constexpr Date next_weekday(const Date& date, Weekday target) noexcept
{
    const date::sys_days sd{utils::to_ymd(date)};
    const date::weekday target_weekday{static_cast<unsigned>(target) + 1};
    return Date{utils::from_ymd(
        date::year_month_day{sd + (target_weekday - date::weekday{sd})})};
}

constexpr Date next_weekday_excluding_current(const Date& date,
                                              Weekday target) noexcept
{
    return next_weekday(date + Days{1}, target);
}

constexpr Date last_day_of_month(const Date& date) noexcept
{
    const auto ymd = utils::to_ymd(date);
    return Date{utils::from_ymd(
        date::year_month_day{ymd.year() / ymd.month() / date::last})};
}

inline constexpr Weekday weekday(const Date& date) noexcept
{
    return static_cast<Weekday>(
        date::weekday(utils::to_ymd(date)).iso_encoding() - 1);
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
            ss << std::setfill('0') << std::setw(4)
               << static_cast<int>(date.year());
            format.remove_prefix(4);
        }
        else if (startsWith(format, "yy")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<int>(date.year()) % 100;
            format.remove_prefix(2);
        }
        else if (startsWith(format, "MM")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<unsigned>(date.month());
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'M')) {
            ss << static_cast<unsigned>(date.month());
            format.remove_prefix(1);
        }
        else if (startsWith(format, "dd")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<unsigned>(date.day());
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'd')) {
            ss << static_cast<unsigned>(date.day());
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
    const auto s_days = date::sys_days{utils::to_ymd(date)} + days;
    return Date{utils::from_ymd(s_days)};
}

inline constexpr Date operator-(const Date& date, const Days& days) noexcept
{
    return date + -days;
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
    auto ymd = utils::to_ymd(date);
    ymd += date::months{months.count()};
    if (!ymd.ok())
        ymd = ymd.year() / ymd.month() / date::last;
    return Date{utils::from_ymd(ymd)};
}

inline constexpr Date operator-(const Date& date, const Months& months) noexcept
{
    return date + -months;
}

inline constexpr Date operator+(const Date& date, const Years& years) noexcept
{
    auto ymd = utils::to_ymd(date) + date::years{years.count()};
    if (!ymd.ok())
        ymd = ymd.year() / ymd.month() / date::last;
    return Date(utils::from_ymd(ymd));
}

inline constexpr Date operator-(const Date& date, const Years& years) noexcept
{
    return date + -years;
}

inline constexpr Date normalize(const Date& date) noexcept
{
    auto ymd = utils::to_ymd(date);
    ymd += date::months{0};
    ymd = date::sys_days{ymd};
    return utils::from_ymd(ymd);
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Date& date)
{
    os << std::setfill('0') << std::setw(2) << static_cast<unsigned>(date.day())
       << '.' << std::setfill('0') << std::setw(2)
       << static_cast<unsigned>(date.month()) << '.'
       << static_cast<int>(date.year());
    return os;
}

inline constexpr bool operator==(const Date& lhs, const Date& rhs) noexcept
{
    return static_cast<int>(lhs.year()) == static_cast<int>(rhs.year()) &&
           static_cast<unsigned>(lhs.month()) ==
               static_cast<unsigned>(rhs.month()) &&
           static_cast<unsigned>(lhs.day()) == static_cast<unsigned>(rhs.day());
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
    return static_cast<int>(lhs.year()) < static_cast<int>(rhs.year())
               ? true
               : (static_cast<int>(lhs.year()) > static_cast<int>(rhs.year())
                      ? false
                      : (static_cast<unsigned>(lhs.month()) <
                                 static_cast<unsigned>(rhs.month())
                             ? true
                             : (static_cast<unsigned>(lhs.month()) >
                                        static_cast<unsigned>(rhs.month())
                                    ? false
                                    : (static_cast<unsigned>(lhs.day()) <
                                       static_cast<unsigned>(rhs.day())))));
}

constexpr bool operator>=(const Date& lhs, const Date& rhs) noexcept
{
    return !(lhs < rhs);
}

constexpr bool operator>(const Date& lhs, const Date& rhs) noexcept
{
    return rhs < lhs;
}

// DateTime implementation

template <typename Clock, typename Duration>
inline constexpr DateTime::DateTime(
    const std::chrono::time_point<Clock, Duration>& timepoint) noexcept
    : ymd{date::year_month_day(std::chrono::floor<date::days>(timepoint))}
    , tod{date::make_time(timepoint -
                          std::chrono::floor<date::days>(timepoint))}
{
}

constexpr DateTime::DateTime(const Date& date) noexcept
    : ymd{utils::to_ymd(date)}
{
}

template <typename Rep, typename Period>
inline constexpr DateTime::DateTime(
    const Date& date,
    const std::chrono::duration<Rep, Period>& time_since_midnight) noexcept
    : ymd{utils::to_ymd(date + std::chrono::floor<Days>(time_since_midnight))}
    , tod{time_since_midnight - std::chrono::floor<Days>(time_since_midnight)}
{
}

constexpr Date DateTime::date() const noexcept { return utils::from_ymd(ymd); }

constexpr Year DateTime::year() const noexcept
{
    return Year{static_cast<int>(ymd.year())};
}

constexpr Month DateTime::month() const noexcept
{
    return Month{static_cast<unsigned>(ymd.month())};
}

constexpr Day DateTime::day() const noexcept
{
    return Day{static_cast<unsigned>(ymd.day())};
}

constexpr DateTime::precision DateTime::time() const noexcept
{
    return tod.to_duration();
}

constexpr std::chrono::hours DateTime::hour() const noexcept
{
    return tod.hours();
}

constexpr std::chrono::minutes DateTime::minute() const noexcept
{
    return tod.minutes();
}

constexpr std::chrono::seconds DateTime::second() const noexcept
{
    return tod.seconds();
}

constexpr Weekday DateTime::weekday() const noexcept
{
    return static_cast<Weekday>(date::weekday(ymd).iso_encoding() - 1);
}

inline DateTime current_date_time() noexcept
{
    return DateTime{std::chrono::system_clock::now()};
}

inline DateTime current_date_time_local() noexcept
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(timepoint);
    std::tm localTime = *std::localtime(&t);
    utils::fill_timepoint(localTime, timepoint);
    return DateTime{timepoint};
}

template <typename ToDuration, typename Clock, typename Duration>
inline constexpr std::chrono::time_point<Clock, ToDuration>
to_time_point(const DateTime& dt) noexcept
{
    using namespace std::chrono;
    return time_point_cast<ToDuration>(sys_days(dt.date())) +
           std::chrono::floor<ToDuration>(dt.time());
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateTime& dt)
{
    os << std::setfill('0') << std::setw(2) << static_cast<unsigned>(dt.day())
       << "." << std::setfill('0') << std::setw(2)
       << static_cast<unsigned>(dt.month()) << "."
       << static_cast<int>(dt.year()) << " " << std::setfill('0')
       << std::setw(2) << dt.hour().count() << ":" << std::setfill('0')
       << std::setw(2) << dt.minute().count() << ":" << std::setfill('0')
       << std::setw(2) << dt.second().count();
    return os;
}

inline std::string to_string(const DateTime& dt, std::string_view format)
{
    return utils::formatDateTime(dt, format);
}

inline constexpr bool operator==(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return lhs.date() == rhs.date() && lhs.time() == rhs.time();
}

inline constexpr bool operator!=(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return !(lhs == rhs);
}

inline constexpr bool operator<(const DateTime& lhs,
                                const DateTime& rhs) noexcept
{
    if (lhs.date() == rhs.date())
        return lhs.time() < rhs.time();
    return lhs.date() < rhs.date();
}

inline constexpr bool operator>(const DateTime& lhs,
                                const DateTime& rhs) noexcept
{
    return rhs < lhs;
}
inline constexpr bool operator<=(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return !(lhs > rhs);
}
inline constexpr bool operator>=(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return !(lhs < rhs);
}

template <typename Rep, typename Period>
inline constexpr DateTime
operator+(const DateTime& dt,
          const std::chrono::duration<Rep, Period>& duration) noexcept
{
    auto whole_days = std::chrono::floor<Days>(duration);
    auto time_since_midnight = duration - whole_days + dt.time();
    const auto overflow_day = std::chrono::floor<Days>(time_since_midnight);
    time_since_midnight -= overflow_day;
    whole_days += overflow_day;
    const Date date{dt.date() + whole_days};
    return DateTime(date, time_since_midnight);
}

template <typename Rep, typename Period>
inline constexpr DateTime
operator-(const DateTime& dt,
          const std::chrono::duration<Rep, Period>& duration) noexcept
{
    return dt + -duration;
}

constexpr DateTime operator+(const DateTime& dt, const Months& months) noexcept
{
    return DateTime{dt.date() + months, dt.time()};
}

constexpr DateTime operator-(const DateTime& dt, const Months& months) noexcept
{
    return dt + -months;
}

constexpr inline DateTime operator+(const DateTime& dt,
                                    const Years& years) noexcept
{
    return DateTime{dt.date() + years, dt.time()};
}

constexpr inline DateTime operator-(const DateTime& dt,
                                    const Years& years) noexcept
{
    return dt + -years;
}

// IsoDate implementation

template <typename Clock, typename Duration>
constexpr IsoDate::IsoDate(
    const std::chrono::time_point<Clock, Duration>& time_point)
    : i_week{date::floor<iso_week::days>(time_point)}
{
}

constexpr IsoDate::IsoDate(const DateTime& dt)
    : i_week{to_time_point<Days>(dt)}
{
}

constexpr IsoDate::IsoDate(const Date& date)
    : IsoDate{DateTime{date}}
{
}

constexpr unsigned IsoDate::weeknum() const noexcept
{
    return static_cast<unsigned>(i_week.weeknum());
}

constexpr Year IsoDate::year() const noexcept
{
    return Year{static_cast<int>(i_week.year())};
}

constexpr Weekday IsoDate::weekday() const noexcept
{
    return static_cast<Weekday>(static_cast<unsigned>(i_week.weekday()) - 1);
}

constexpr inline bool operator==(const IsoDate& lhs,
                                 const IsoDate& rhs) noexcept
{
    return lhs.i_week == rhs.i_week;
}

// DateRange implementation

constexpr DateRange::DateRange(Date start, Date finish) noexcept
    : start_{std::move(start)}
    , finish_{std::move(finish)}
{
}

constexpr Date DateRange::start() const noexcept { return start_; }

constexpr Date DateRange::finish() const noexcept { return finish_; }

constexpr Days DateRange::duration() const noexcept
{
    const date::sys_days ds_start{utils::to_ymd(start_)};
    const date::sys_days ds_finish{utils::to_ymd(finish_)};
    return date::abs(ds_finish - ds_start);
}

inline constexpr bool operator==(const DateRange& lhs, const DateRange& rhs)
{
    return lhs.start() == rhs.start() && lhs.finish() == rhs.finish();
}

inline constexpr bool operator!=(const DateRange& lhs, const DateRange& rhs)
{
    return !(lhs == rhs);
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateRange& ds)
{
    os << "DateRange {" << ds.start() << " - " << ds.finish() << "}";
    return os;
}

constexpr DateRange add_offset(const DateRange& date_range,
                               const Days& offset) noexcept
{
    return DateRange{date_range.start() + offset, date_range.finish() + offset};
}

inline std::string
to_string(const DateRange& ds, std::string_view format, std::string sep)
{
    std::stringstream ss;
    ss << to_string(ds.start(), format) << sep
       << to_string(ds.finish(), format);
    return ss.str();
}

// DateTimeRange implementation

template <typename Clock, typename Duration>
inline constexpr DateTimeRange::DateTimeRange(
    const std::chrono::time_point<Clock, Duration>& start,
    const std::chrono::time_point<Clock, Duration>& finish) noexcept
    : start_{DateTime{start}}
    , finish_{DateTime{finish}}
{
}

constexpr DateTimeRange::DateTimeRange(const DateTime& start,
                                       const DateTime& finish) noexcept
    : start_{start}
    , finish_{finish}
{
}

constexpr DateTime DateTimeRange::start() const noexcept { return start_; }

constexpr DateTime DateTimeRange::finish() const noexcept { return finish_; }

template <typename ToDuration>
inline constexpr ToDuration DateTimeRange::duration() const noexcept
{
    using namespace std::chrono;
    static_assert(utils::is_chrono_duration<ToDuration>::value,
                  "duration must be a std::chrono::duration");
    return date::abs(to_time_point<ToDuration>(finish_) -
                     to_time_point<ToDuration>(start_));
}

inline std::string to_string(const DateTimeRange& date_time_range,
                             std::string_view format,
                             std::string sep)
{
    std::stringstream ss;
    std::string separator{std::move(sep)};
    ss << to_string(date_time_range.start(), format) << separator
       << to_string(date_time_range.finish(), format);
    return ss.str();
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateTimeRange& span)
{
    os << "DateTimeRange {" << span.start() << ", " << span.finish() << "}";
    return os;
}

inline constexpr bool operator!=(const DateTimeRange& lhs,
                                 const DateTimeRange& rhs) noexcept
{
    return lhs.start() != rhs.start() || lhs.finish() != rhs.finish();
}

inline bool constexpr operator==(const DateTimeRange& lhs,
                                 const DateTimeRange& rhs) noexcept
{
    return !(lhs != rhs);
}

inline constexpr DateTimeRange add_offset(const DateTimeRange& dt_range,
                                          std::chrono::seconds offset) noexcept
{
    return DateTimeRange{dt_range.start() + offset, dt_range.finish() + offset};
}

namespace utils {

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
    return date::weekday{static_cast<unsigned>(weekday) + 1};
}

/* Convert std::tm to std::chrono::timepoint. */
template <typename Clock, typename Duration>
inline void fill_timepoint(const std::tm& t,
                           std::chrono::time_point<Clock, Duration>& tp)
{
    using namespace std::chrono;
    using namespace date;
    int y = t.tm_year + 1900;
    auto ymd = year(y) / (t.tm_mon + 1) / t.tm_mday;
    if (!ymd.ok())
        throw std::runtime_error("Invalid date");
    tp = sys_days(ymd) + hours(t.tm_hour) + minutes(t.tm_min) +
         seconds(t.tm_sec);
}

inline std::string formatDateTime(const dw::DateTime& dt,
                                  std::string_view format)
{
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
            ss << std::setfill('0') << std::setw(4)
               << static_cast<int>(dt.year());
            format.remove_prefix(4);
        }
        else if (startsWith(format, "yy")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<int>(dt.year()) % 100;
            format.remove_prefix(2);
        }
        else if (startsWith(format, "MM")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<unsigned>(dt.month());
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'M')) {
            ss << static_cast<unsigned>(dt.month());
            format.remove_prefix(1);
        }
        else if (startsWith(format, "dd")) {
            ss << std::setfill('0') << std::setw(2)
               << static_cast<unsigned>(dt.day());
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'd')) {
            ss << static_cast<unsigned>(dt.day());
            format.remove_prefix(1);
        }
        else if (startsWith(format, "hh")) {
            ss << std::setfill('0') << std::setw(2) << dt.hour().count();
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'h')) {
            ss << dt.hour().count();
            format.remove_prefix(1);
        }
        else if (startsWith(format, "mm")) {
            ss << std::setfill('0') << std::setw(2) << dt.minute().count();
            format.remove_prefix(2);
        }
        else if (startsWith(format, 'm')) {
            ss << dt.minute().count();
            format.remove_prefix(1);
        }
        else if (startsWith(format, "ss")) {
            ss << std::setfill('0') << std::setw(2) << dt.second().count();
            format.remove_prefix(2);
        }
        else if (startsWith(format, 's')) {
            ss << dt.second().count();
            format.remove_prefix(1);
        }
        else {
            ss << format.front();
            format.remove_prefix(1);
        }
    }

    return ss.str();
}

constexpr Date from_ymd(const date::year_month_day& ymd) noexcept
{
    return Date{Year{static_cast<int>(ymd.year())},
                Month{static_cast<unsigned>(ymd.month())},
                Day{static_cast<unsigned>(ymd.day())}};
}

constexpr date::year_month_day to_ymd(const Date& date) noexcept
{
    return date::year_month_day{
        date::year{static_cast<int>(date.year())},
        date::month{static_cast<unsigned>(date.month())},
        date::day{static_cast<unsigned>(date.day())}};
}

template <class Duration, class Rep, class Period>
inline Duration checked_convert(std::chrono::duration<Rep, Period> d)
{
    using namespace std::chrono;
    using S = duration<double, typename Duration::period>;
    constexpr S m = Duration::min();
    constexpr S M = Duration::max();
    S s = d;
    if (s < m || s > M)
        throw std::overflow_error("checked_convert");
    return duration_cast<Duration>(s);
}

} // namespace utils

} // namespace dw

#endif /* end of include guard: DATE_WRAPPER_H_XU053LKE */
