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
#ifndef DATETIME_H_RTJVB37W
#define DATETIME_H_RTJVB37W

#include "date.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace dw {

class DateTime;

namespace {
    using namespace dw;

    /* Convert std::tm to std::chrono::timepoint. */
    template <typename Clock, typename Duration>
    void to_time_point(const std::tm& t,
                       std::chrono::time_point<Clock, Duration>& tp);

    constexpr std::array<unsigned, 7> mondayFirstTable{
        {6u, 0u, 1u, 2u, 3u, 4u, 5u}};

    bool endsWith(const std::string& str, const std::string& suffix);

    std::string formatDateTime(const DateTime& dt, std::string&& format);

    constexpr date::year_month_day normalize(date::year_month_day ymd) noexcept;

    template <typename T>
    struct is_chrono_duration {
        static constexpr bool value = false;
    };

    template <typename Rep, typename Period>
    struct is_chrono_duration<std::chrono::duration<Rep, Period>> {
        static constexpr bool value = true;
    };
}

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

    enum class Weekday {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

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

    static DateTime currentDateTime() noexcept;

    /* Not thread-safe */
    static DateTime currentDateTimeLocal() noexcept;

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
    constexpr Duration differenceBetween(const DateTime& other) const noexcept;

    /* Return distance in calendar days to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative.
     *
     * Number of days returned is a number of times midnight is encountered
     * between two DateTime objects. So distance between 11.04.2016 23:59 and
     * 12.04.2016 00:01 is equal to one day. */
    constexpr int discreteDaysTo(const DateTime& other) const noexcept;

    /* Return distance in calendar months to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative. */
    constexpr int discreteMonthsTo(const DateTime& other) const noexcept;

    template <class Duration>
    constexpr long long discreteDistanceTo(const DateTime& other) const
        noexcept;

    /* Return distance in calendar years to other DateTime object.
     *
     * If other DateTime object is behind in time, result will be negative. */
    constexpr int discreteYearsTo(const DateTime& other) const noexcept;

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

inline constexpr DateTime::DateTime(
    std::chrono::system_clock::time_point timepoint) noexcept
    : time{timepoint}
    , ymd{date::year_month_day(date::floor<date::days>(time))}
    , tod{date::make_time(time - date::floor<date::days>(time))}
{
}

/* static */
constexpr DateTime DateTime::fromYMD(int year, int month, int day)
{
    date::year_month_day dateYMD{date::year(year) / month / day};
    if (!dateYMD.ok())
        throw std::runtime_error("Invalid date");
    std::chrono::system_clock::time_point tp = date::sys_days(dateYMD);
    return DateTime{tp};
}

/* static */
inline DateTime DateTime::fromTime_t(std::time_t timeT,
                                     int offsetFromUtcInSeconds) noexcept
{
    return DateTime{std::chrono::system_clock::from_time_t(timeT)
                    + std::chrono::seconds{offsetFromUtcInSeconds}};
}

/* static */
template <typename Duration>
inline constexpr DateTime
DateTime::fromTimestamp(long long timestamp,
                        int offsetFromUtcInSeconds) noexcept
{
    static_assert(is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    std::chrono::system_clock::time_point time_point{
        Duration(timestamp) + std::chrono::seconds(offsetFromUtcInSeconds)};
    return DateTime{time_point};
}

/* static */
constexpr DateTime
DateTime::fromUnixTimestamp(long long timestamp,
                            int offsetFromUtcInSeconds) noexcept
{
    return DateTime::fromTimestamp(timestamp, offsetFromUtcInSeconds);
}

/* static */
inline DateTime DateTime::currentDateTime() noexcept
{
    return DateTime{std::chrono::system_clock::now()};
}

/* static */
inline DateTime DateTime::currentDateTimeLocal() noexcept
{
    auto timepoint = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(timepoint);
    std::tm localTime = *std::localtime(&t);
    to_time_point(localTime, timepoint);
    return DateTime{timepoint};
}

inline std::time_t DateTime::toTime_t() const noexcept
{
    return std::chrono::system_clock::to_time_t(time);
}

template <typename Duration>
inline constexpr DateTime DateTime::add(Duration duration) const noexcept
{
    static_assert(is_chrono_duration<Duration>::value,
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
    t = normalize(t);
    auto d
        = sys_days{t} + hours{hour()} + minutes{minute()} + seconds{second()};

    return DateTime{d};
}

template <typename Duration>
inline constexpr Duration
DateTime::differenceBetween(const DateTime& other) const noexcept
{
    using namespace std::chrono;
    static_assert(is_chrono_duration<Duration>::value,
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
    static_assert(is_chrono_duration<Duration>::value,
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
    static_assert(is_chrono_duration<Duration>::value,
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

constexpr DateTime::Weekday DateTime::dayOfWeek() const noexcept
{
    auto dayNumber
        = mondayFirstTable[static_cast<unsigned>(date::weekday(ymd))];
    return static_cast<DateTime::Weekday>(dayNumber);
}

inline std::string DateTime::toString(std::string format) const
{
    return formatDateTime(*this, std::move(format));
}

inline std::ostream& operator<<(std::ostream& os, const DateTime& dt)
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

namespace {

    template <typename Clock, typename Duration>
    void to_time_point(const std::tm& t,
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

    inline constexpr date::year_month_day
    normalize(date::year_month_day ymd) noexcept
    {
        using namespace date;
        if (!ymd.ok())
            return ymd.year() / ymd.month() / last;
        return ymd;
    }

    template <typename T>
    void pop_back_n(T& container, size_t n)
    {
        auto limit = std::min(n, container.size());
        for (size_t i = 0; i < limit; ++i)
            container.pop_back();
    }

    bool endsWith(const std::string& str, const std::string& suffix)
    {
        if (suffix.size() > str.size())
            return false;
        return std::equal(suffix.crbegin(), suffix.crend(), str.crbegin());
    }

    std::string formatDateTime(const DateTime& dt, std::string&& format)
    {
        std::stringstream ss;

        std::string f{std::move(format)};
        std::reverse(f.begin(), f.end());

        while (!f.empty()) {
            if (endsWith(f, "''")) {
                ss << "'";
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "'")) {
                pop_back_n(f, 1);
                auto m = f.find_last_of("'");
                if (m != std::string::npos) {
                    while (!endsWith(f, "'")) {
                        ss << f.back();
                        f.pop_back();
                    }
                    f.pop_back();
                }
            }
            else if (endsWith(f, "yyyy")) {
                ss << std::setfill('0') << std::setw(4) << dt.year();
                pop_back_n(f, 4);
            }
            else if (endsWith(f, "yy")) {
                ss << std::setfill('0') << std::setw(2) << dt.year() % 100;
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "MM")) {
                ss << std::setfill('0') << std::setw(2) << dt.month();
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "M")) {
                ss << dt.month();
                pop_back_n(f, 1);
            }
            else if (endsWith(f, "dd")) {
                ss << std::setfill('0') << std::setw(2) << dt.day();
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "d")) {
                ss << dt.day();
                pop_back_n(f, 1);
            }
            else if (endsWith(f, "hh")) {
                ss << std::setfill('0') << std::setw(2) << dt.hour();
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "h")) {
                ss << dt.hour();
                pop_back_n(f, 1);
            }
            else if (endsWith(f, "mm")) {
                ss << std::setfill('0') << std::setw(2) << dt.minute();
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "m")) {
                ss << dt.minute();
                pop_back_n(f, 1);
            }
            else if (endsWith(f, "ss")) {
                ss << std::setfill('0') << std::setw(2) << dt.second();
                pop_back_n(f, 2);
            }
            else if (endsWith(f, "s")) {
                ss << dt.second();
                pop_back_n(f, 1);
            }
            else {
                ss << f.back();
                f.pop_back();
            }
        }

        return ss.str();
    }

} // namespace

} // namespace dw

#endif /* end of include guard: DATETIME_H_RTJVB37W */
