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

using Days = date::days;
using Weeks = date::weeks;
using Months = date::months;
using Years = date::years;

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


/* Immutable datatype that provides date and time functions.
 *
 * It is a wrapper around Howard Hinnant's date library
 * https://github.com/HowardHinnant */
class DateTime {
public:
    using Days = date::days;
    using Months = date::months;
    using Years = date::years;
    using precision = std::chrono::system_clock::duration;

    constexpr DateTime(
        std::chrono::system_clock::time_point timepoint) noexcept;

    /* Construct DateTime with given date.
     * Time is set to midnight. */
    constexpr static DateTime fromYMD(int year, int month, int day);

    static DateTime fromTime_t(std::time_t timeT,
                               int offsetFromUtcInSeconds = 0) noexcept;

    constexpr static DateTime fromUnixTimestamp(long long timestamp,
                                                int offsetFromUtcInSeconds
                                                = 0) noexcept;

    /* Construct DateTime from timestamp of arbitrary precision
     * expressed as std::chrono::duration
     * Timestamp is expected to be counter from 00:00:00 UTC on 1 January 1970
     */
    template <typename Duration = std::chrono::seconds>
    constexpr static DateTime
    fromTimestamp(long long timestamp, int offsetFromUtcInSeconds = 0) noexcept;

    [[deprecated]] static DateTime currentDateTime() noexcept;

    /* Not thread-safe */
    [[deprecated]] static DateTime currentDateTimeLocal() noexcept;

    /* Return std::time_t representation. */
    std::time_t toTime_t() const noexcept;

    /* Return new DateTime object that stands apart in time by given duration.
     * Duration template parameter is restricted to std::chono::duration type.
     */
    template <typename Duration>
    constexpr DateTime add(Duration duration) const noexcept;

    constexpr DateTime add(DateTime::Months duration) const noexcept;

    constexpr DateTime add(DateTime::Years duration) const noexcept;

    /* Return difference between this and other's DateTime objects' timepoints
     * with specified duration as understood by std::chrono library.
     * Duration template parameter must be of std::chrono::duration type.
     * Result is rounded towards zero.
     */
    template <typename Duration = std::chrono::system_clock::duration>
    [[deprecated]] constexpr Duration
    differenceBetween(const DateTime& other) const noexcept;

    /* Return distance in calendar days to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative.
     *
     * Number of days returned is a number of times midnight is encountered
     * between two DateTime objects. So distance between 11.04.2016 23:59 and
     * 12.04.2016 00:01 is equal to one day. */
    [[deprecated]] constexpr int discreteDaysTo(const DateTime& other) const
        noexcept;

    /* Return distance in calendar months to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative. */
    [[deprecated]] constexpr int discreteMonthsTo(const DateTime& other) const
        noexcept;

    template <class Duration>
    [[deprecated]] constexpr long long
    discreteDistanceTo(const DateTime& other) const noexcept;

    /* Return distance in calendar years to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative. */
    [[deprecated]] constexpr int discreteYearsTo(const DateTime& other) const
        noexcept;

    /* Return chrono time_point. */
    constexpr std::chrono::system_clock::time_point chronoTimepoint() const
        noexcept;

    /* Return timestamp with specified std::chrono::duration.
     * By default, returns number of seconds since start of the Unix epoch. */
    template <class Duration = std::chrono::seconds>
    constexpr long long timestamp() const noexcept;

    /* Returns number of seconds since Unix epoch.
     * Alias for timestamp<std::chrono::seconds>() */
    constexpr long long unix_timestamp() const noexcept;

    /* Return year as integer. */
    constexpr int year() const noexcept;

    /* Return month as unsigned integer in [1, 12]. */
    constexpr unsigned month() const noexcept;

    /* Return day as unsigned integer in [1, 31]. */
    constexpr unsigned day() const noexcept;

    /* Return hours since midnight in 24-h format. */
    constexpr long hour() const noexcept;

    /* Return minutes since the start of the hour. */
    constexpr long minute() const noexcept;

    /* Return seconds since the start of the minute. */
    constexpr long long second() const noexcept;

    /* Return day of week. */
    constexpr Weekday dayOfWeek() const noexcept;

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
    std::string toString(std::string format) const;

    friend constexpr bool operator==(const DateTime& dt1,
                                     const DateTime& dt2) noexcept;

    friend constexpr bool operator!=(const DateTime& dt1,
                                     const DateTime& dt2) noexcept;

    friend constexpr bool operator<(const DateTime& dt1,
                                    const DateTime& dt2) noexcept;

    friend constexpr bool operator<=(const DateTime& dt1,
                                     const DateTime& dt2) noexcept;

    friend constexpr bool operator>(const DateTime& dt1,
                                    const DateTime& dt2) noexcept;

    friend constexpr bool operator>=(const DateTime& dt1,
                                     const DateTime& dt2) noexcept;

private:
    std::chrono::system_clock::time_point time;
    date::year_month_day ymd;
    date::time_of_day<std::chrono::system_clock::duration> tod;
};

DateTime current_date_time() noexcept;

/* Not thread-safe */
DateTime current_date_time_local() noexcept;


class IsoDate {
public:
    constexpr IsoDate(const DateTime& dt);

    constexpr unsigned weeknum() const noexcept;

    constexpr int year() const noexcept;

    constexpr unsigned weekday() const noexcept;

    friend constexpr bool operator==(const IsoDate& lhs,
                                     const IsoDate& rhs) noexcept;

private:
    const iso_week::year_weeknum_weekday i_week;
};


/* Represent finite interval of dates. */
class DateSpan {
public:
    constexpr DateSpan(Date start, Date finish) noexcept;

    constexpr Date start() const noexcept;

    constexpr Date finish() const noexcept;

    /* Returns duration in Days (that is std::chrono::duration type). */
    constexpr Days duration() const noexcept;

private:
    Date start_;
    Date finish_;
};

constexpr bool operator==(const DateSpan& lhs, const DateSpan& rhs);

constexpr bool operator!=(const DateSpan& lhs, const DateSpan& rhs);

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateSpan& ds);

std::string
to_string(const DateSpan& ds, std::string_view format, std::string sep = " - ");


/* Represent finite interval in time with start and finish points. */
struct TimeSpan {

    using SystemClock = std::chrono::system_clock::time_point;

    constexpr DateTime start() const noexcept;
    constexpr DateTime finish() const noexcept;

    /* Construct from chrono time_point. */
    constexpr TimeSpan(SystemClock start, SystemClock finish) noexcept;

    constexpr TimeSpan(DateTime start, DateTime finish) noexcept;

    /* Construct from std::time_t start and finish points. */
    TimeSpan(std::time_t start,
             std::time_t finish,
             int offsetFromUtcInSeconds = 0) noexcept;

    /* Return size of TimeInterval with specified Duration.
     * Duration is restricted to std::chrono::duration type.
     */
    template <class Duration>
    constexpr Duration duration() const noexcept;

    /* Return string representation of TimeSpan. The result is determined
     * by format string that is applied both to start and finish DateTime
     * objects, separated by sep string.
     * See also documentation for DateTime::toString.
     */
    std::string toString(const std::string& format,
                         std::string sep = " - ") const;

    friend std::ostream& operator<<(std::ostream& os, const TimeSpan& span);

private:
    DateTime startTime;
    DateTime finishTime;
};


namespace utils {

    constexpr std::array<unsigned, 7> mondayFirstTable{
        {6u, 0u, 1u, 2u, 3u, 4u, 5u}};

    constexpr std::array<unsigned, 7> sundayFirstTable{
        {1u, 2u, 3u, 4u, 5u, 6u, 0u}};

    constexpr date::year_month_day normalize(date::year_month_day ymd) noexcept;

    bool startsWith(std::string_view str, std::string_view prefix);

    bool startsWith(std::string_view str, char ch);

    constexpr date::weekday convert(dw::Weekday weekday) noexcept;

    /* Convert std::tm to std::chrono::timepoint. */
    template <typename Clock, typename Duration>
    void to_time_point(const std::tm& t,
                       std::chrono::time_point<Clock, Duration>& tp);

    template <typename T>
    struct is_chrono_duration {
        static constexpr bool value = false;
    };

    template <typename Rep, typename Period>
    struct is_chrono_duration<std::chrono::duration<Rep, Period>> {
        static constexpr bool value = true;
    };

    std::string formatDateTime(const DateTime& dt, std::string_view format);

} // namespace utils


// Year implementation

constexpr Year::Year(int year) noexcept
    : year_{year}
{
}

constexpr int Year::value() const noexcept { return int{year_}; }

constexpr Year::operator int() const noexcept { return int{year_}; }


// Month implementation

constexpr Month::Month(unsigned month) noexcept
    : month_{static_cast<decltype(month_)>(month)}
{
}

constexpr unsigned Month::value() const noexcept
{
    return static_cast<unsigned>(month_);
}


// Day implementation

constexpr Day::Day(unsigned day) noexcept
    : day_{static_cast<decltype(day_)>(day)}
{
}

constexpr unsigned Day::value() const noexcept
{
    return static_cast<unsigned>(day_);
}


// Date implementation

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


// DateTime implementation

inline constexpr DateTime::DateTime(
    std::chrono::system_clock::time_point timepoint) noexcept
    : time{timepoint}
    , ymd{date::year_month_day(std::chrono::floor<date::days>(time))}
    , tod{date::make_time(time - std::chrono::floor<date::days>(time))}
{
}

constexpr DateTime DateTime::fromYMD(int year, int month, int day)
{
    date::year_month_day dateYMD{date::year(year) / month / day};
    if (!dateYMD.ok())
        throw std::runtime_error("Invalid date");
    std::chrono::system_clock::time_point tp = date::sys_days(dateYMD);
    return DateTime{tp};
}

inline DateTime DateTime::fromTime_t(std::time_t timeT,
                                     int offsetFromUtcInSeconds) noexcept
{
    return DateTime{std::chrono::system_clock::from_time_t(timeT)
                    + std::chrono::seconds{offsetFromUtcInSeconds}};
}

template <typename Duration>
inline constexpr DateTime
DateTime::fromTimestamp(long long timestamp,
                        int offsetFromUtcInSeconds) noexcept
{
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    std::chrono::system_clock::time_point time_point{
        Duration(timestamp) + std::chrono::seconds(offsetFromUtcInSeconds)};
    return DateTime{time_point};
}

constexpr DateTime
DateTime::fromUnixTimestamp(long long timestamp,
                            int offsetFromUtcInSeconds) noexcept
{
    return DateTime::fromTimestamp(timestamp, offsetFromUtcInSeconds);
}

inline DateTime DateTime::currentDateTime() noexcept
{
    return DateTime{std::chrono::system_clock::now()};
}

inline DateTime DateTime::currentDateTimeLocal() noexcept
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(timepoint);
    std::tm localTime = *std::localtime(&t);
    utils::to_time_point(localTime, timepoint);
    return DateTime{timepoint};
}

inline std::time_t DateTime::toTime_t() const noexcept
{
    return std::chrono::system_clock::to_time_t(time);
}

template <typename Duration>
inline constexpr DateTime DateTime::add(Duration duration) const noexcept
{
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return DateTime{time + duration};
}

constexpr DateTime DateTime::add(DateTime::Months duration) const noexcept
{
    using namespace date;
    using namespace std::chrono;
    auto y = year_month{date::year(year()), date::month(month())}
        + date::months{duration.count()};
    auto t = year_month_day{y.year(), y.month(), date::day(day())};
    t = utils::normalize(t);
    auto d
        = sys_days{t} + hours{hour()} + minutes{minute()} + seconds{second()};

    return DateTime{d};
}

template <typename Duration>
inline constexpr Duration
DateTime::differenceBetween(const DateTime& other) const noexcept
{
    using namespace std::chrono;
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return duration_cast<Duration>(other.time - time);
}

constexpr DateTime DateTime::add(DateTime::Years duration) const noexcept
{
    return add(std::chrono::duration_cast<DateTime::Months>(duration));
}

constexpr int DateTime::discreteDaysTo(const DateTime& other) const noexcept
{
    using namespace date;
    return (sys_days(other.ymd) - sys_days(ymd)).count();
}

constexpr int DateTime::discreteMonthsTo(const DateTime& other) const noexcept
{
    using namespace date;
    return (year_month{other.ymd.year(), other.ymd.month()}
            - year_month{ymd.year(), ymd.month()})
        .count();
}

constexpr int DateTime::discreteYearsTo(const DateTime& other) const noexcept
{
    using namespace date;
    return (other.ymd.year() - ymd.year()).count();
}

template <class Duration>
inline constexpr long long
DateTime::discreteDistanceTo(const DateTime& other) const noexcept
{
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return date::ceil<Duration>(other.time - time);
}

constexpr std::chrono::system_clock::time_point
DateTime::chronoTimepoint() const noexcept
{
    return time;
}

template <class Duration>
constexpr long long DateTime::timestamp() const noexcept
{
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return std::chrono::duration_cast<Duration>(time.time_since_epoch())
        .count();
}

constexpr long long DateTime::unix_timestamp() const noexcept
{
    return timestamp<std::chrono::seconds>();
}

constexpr int DateTime::year() const noexcept { return int(ymd.year()); }

constexpr unsigned DateTime::month() const noexcept
{
    return unsigned(ymd.month());
}

constexpr unsigned DateTime::day() const noexcept
{
    return unsigned(ymd.day());
}

constexpr long DateTime::hour() const noexcept { return tod.hours().count(); }

constexpr long DateTime::minute() const noexcept
{
    return tod.minutes().count();
}

constexpr long long DateTime::second() const noexcept
{
    return tod.seconds().count();
}

constexpr Weekday DateTime::dayOfWeek() const noexcept
{
    auto dayNumber
        = utils::mondayFirstTable[static_cast<unsigned>(date::weekday(ymd))];
    return static_cast<Weekday>(dayNumber);
}

inline std::string DateTime::toString(std::string format) const
{
    return utils::formatDateTime(*this, std::move(format));
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
    utils::to_time_point(localTime, timepoint);
    return DateTime{timepoint};
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateTime& dt)
{
    os << std::setfill('0') << std::setw(2) << dt.day() << "."
       << std::setfill('0') << std::setw(2) << dt.month() << "." << dt.year()
       << " " << std::setfill('0') << std::setw(2) << dt.hour() << ":"
       << std::setfill('0') << std::setw(2) << dt.minute() << ":"
       << std::setfill('0') << std::setw(2) << dt.second();
    return os;
}

constexpr inline bool operator==(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return lhs.time == rhs.time;
}

inline constexpr bool operator!=(const DateTime& lhs,
                                 const DateTime& rhs) noexcept
{
    return !(lhs == rhs);
}

inline constexpr bool operator<(const DateTime& lhs,
                                const DateTime& rhs) noexcept
{
    return lhs.time < rhs.time;
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


// IsoDate implementation

constexpr IsoDate::IsoDate(const DateTime& dt)
    : i_week{date::floor<iso_week::days>(dt.chronoTimepoint())}
{
}

constexpr unsigned IsoDate::weeknum() const noexcept
{
    return static_cast<unsigned>(i_week.weeknum());
}

constexpr int IsoDate::year() const noexcept
{
    return static_cast<int>(i_week.year());
}

constexpr unsigned IsoDate::weekday() const noexcept
{
    return static_cast<unsigned>(i_week.weekday());
}

constexpr inline bool operator==(const IsoDate& lhs,
                                 const IsoDate& rhs) noexcept
{
    return lhs.i_week == rhs.i_week;
}


// DateSpan implementation

constexpr DateSpan::DateSpan(Date start, Date finish) noexcept
    : start_{std::move(start)}
    , finish_{std::move(finish)}
{
}

constexpr Date DateSpan::start() const noexcept { return start_; }

constexpr Date DateSpan::finish() const noexcept { return finish_; }

constexpr Days DateSpan::duration() const noexcept
{
    using namespace std::chrono;
    date::sys_days ds_start{
        date::year_month_day{date::year{start_.year().value()},
                             date::month{start_.month().value()},
                             date::day{start_.day().value()}}};
    date::sys_days ds_finish{
        date::year_month_day{date::year{finish_.year().value()},
                             date::month{finish_.month().value()},
                             date::day{finish_.day().value()}}};
    return date::abs(ds_finish - ds_start);
}

inline constexpr bool operator==(const DateSpan& lhs, const DateSpan& rhs)
{
    return lhs.start() == rhs.start() && lhs.finish() == rhs.finish();
}

inline constexpr bool operator!=(const DateSpan& lhs, const DateSpan& rhs)
{
    return !(lhs == rhs);
}

template <class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const DateSpan& ds)
{
    os << "DateSpan {" << ds.start() << " - " << ds.finish() << "}";
    return os;
}

inline std::string
to_string(const DateSpan& ds, std::string_view format, std::string sep)
{
    std::stringstream ss;
    ss << to_string(ds.start(), format) << sep
       << to_string(ds.finish(), format);
    return ss.str();
}


// TimeSpan implementation

constexpr TimeSpan::TimeSpan(SystemClock start, SystemClock finish) noexcept
    : startTime{DateTime{std::move(start)}}
    , finishTime{DateTime{std::move(finish)}}
{
}

constexpr TimeSpan::TimeSpan(DateTime start, DateTime finish) noexcept
    : startTime{std::move(start)}
    , finishTime{std::move(finish)}
{
}

inline TimeSpan::TimeSpan(std::time_t start,
                          std::time_t finish,
                          int offsetFromUtcInSeconds) noexcept
    : startTime{DateTime::fromTime_t(start, offsetFromUtcInSeconds)}
    , finishTime{DateTime::fromTime_t(finish, offsetFromUtcInSeconds)}
{
}

constexpr DateTime TimeSpan::start() const noexcept { return startTime; }

constexpr DateTime TimeSpan::finish() const noexcept { return finishTime; }

template <class Duration>
inline constexpr Duration TimeSpan::duration() const noexcept
{
    using namespace std::chrono;
    static_assert(utils::is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return date::abs(duration_cast<Duration>(finishTime.chronoTimepoint()
                                             - startTime.chronoTimepoint()));
}

inline std::string TimeSpan::toString(const std::string& format,
                                      std::string sep) const
{
    std::stringstream ss;
    std::string separator{std::move(sep)};
    ss << startTime.toString(format) << separator
       << finishTime.toString(format);
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& os, const TimeSpan& span)
{
    os << "TimeSpan {" << span.startTime << ", " << span.finishTime << "}";
    return os;
}

inline bool operator!=(const TimeSpan& lhs, const TimeSpan& rhs)
{
    return lhs.start() != rhs.start() || lhs.finish() != rhs.finish();
}

inline bool operator==(const TimeSpan& lhs, const TimeSpan& rhs)
{
    return !(lhs != rhs);
}

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
        return date::weekday{
            sundayFirstTable[static_cast<unsigned>(weekday) + 1]};
    }

    /* Convert std::tm to std::chrono::timepoint. */
    template <typename Clock, typename Duration>
    inline void to_time_point(const std::tm& t,
                              std::chrono::time_point<Clock, Duration>& tp)
    {
        using namespace std::chrono;
        using namespace date;
        int y = t.tm_year + 1900;
        auto ymd = year(y) / (t.tm_mon + 1) / t.tm_mday;
        if (!ymd.ok())
            throw std::runtime_error("Invalid date");
        tp = sys_days(ymd) + hours(t.tm_hour) + minutes(t.tm_min)
            + seconds(t.tm_sec);
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
                ss << std::setfill('0') << std::setw(4) << dt.year();
                format.remove_prefix(4);
            }
            else if (startsWith(format, "yy")) {
                ss << std::setfill('0') << std::setw(2) << dt.year() % 100;
                format.remove_prefix(2);
            }
            else if (startsWith(format, "MM")) {
                ss << std::setfill('0') << std::setw(2) << dt.month();
                format.remove_prefix(2);
            }
            else if (startsWith(format, 'M')) {
                ss << dt.month();
                format.remove_prefix(1);
            }
            else if (startsWith(format, "dd")) {
                ss << std::setfill('0') << std::setw(2) << dt.day();
                format.remove_prefix(2);
            }
            else if (startsWith(format, 'd')) {
                ss << dt.day();
                format.remove_prefix(1);
            }
            else if (startsWith(format, "hh")) {
                ss << std::setfill('0') << std::setw(2) << dt.hour();
                format.remove_prefix(2);
            }
            else if (startsWith(format, 'h')) {
                ss << dt.hour();
                format.remove_prefix(1);
            }
            else if (startsWith(format, "mm")) {
                ss << std::setfill('0') << std::setw(2) << dt.minute();
                format.remove_prefix(2);
            }
            else if (startsWith(format, 'm')) {
                ss << dt.minute();
                format.remove_prefix(1);
            }
            else if (startsWith(format, "ss")) {
                ss << std::setfill('0') << std::setw(2) << dt.second();
                format.remove_prefix(2);
            }
            else if (startsWith(format, 's')) {
                ss << dt.second();
                format.remove_prefix(1);
            }
            else {
                ss << format.front();
                format.remove_prefix(1);
            }
        }

        return ss.str();
    }
} // namespace utils

} // namespace dw


#endif /* end of include guard: DATE_WRAPPER_H_XU053LKE */
