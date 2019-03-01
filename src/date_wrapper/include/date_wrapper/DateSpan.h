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
#ifndef DATESPAN_H_G3UA50SJ
#define DATESPAN_H_G3UA50SJ

#include "date_wrapper/Date.h"

namespace dw {

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

} // namespace dw

#endif /* end of include guard: DATESPAN_H_G3UA50SJ */
