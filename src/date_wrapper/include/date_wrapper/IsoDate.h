#ifndef ISODATE_H_OH1XK4ZF
#define ISODATE_H_OH1XK4ZF

#include "date_wrapper/DateTime.h"
#include <date/iso_week.h>

namespace dw {

class IsoDate {
public:
    constexpr IsoDate(const DateTime& dt);

    constexpr unsigned weeknum() const noexcept;

    constexpr int year() const noexcept;

    constexpr unsigned weekday() const noexcept;

    friend constexpr bool operator==(const IsoDate& lhs, const IsoDate& rhs) noexcept;

private:
    const iso_week::year_weeknum_weekday i_week;
};

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

constexpr inline bool operator==(const IsoDate& lhs, const IsoDate& rhs) noexcept
{
    return lhs.i_week == rhs.i_week;
}

} // namespace dw

#endif /* end of include guard: ISODATE_H_OH1XK4ZF */
