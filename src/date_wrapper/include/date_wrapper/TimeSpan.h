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
#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "DateTime.h"
#include <chrono>
#include <ostream>

namespace dw {

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
    static_assert(is_chrono_duration<Duration>::value,
                  "duration must be a std::chrono::duration");
    return date::abs(duration_cast<Duration>(finishTime.chronoTimepoint()
                                             - startTime.chronoTimepoint()));
}

inline std::string TimeSpan::toString(const std::string& format, std::string sep) const
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

} // namespace dw

#endif /* end of include guard: TIMEINTERVAL_H */
