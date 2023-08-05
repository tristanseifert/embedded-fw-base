#ifndef UTIL_DATE_H
#define UTIL_DATE_H

#include <stddef.h>
#include <stdint.h>

#include <etl/span.h>

namespace Util {
/**
 * @brief Type for UNIX timestamp
 *
 * Define this to be a 32-bit integer. We'll suffer from the Year 2038 problem though.
 */
typedef uint32_t Timestamp;


/**
 * @brief A point in time, decomposed into its components
 *
 * Represents a single moment in time, as a separate decomposed date and time.
 */
struct Date {
    /// Enum representing the weekday
    enum class Weekday: uint8_t {
        Monday      = 0,
        Tuesday     = 1,
        Wednesday   = 2,
        Thursday    = 3,
        Friday      = 4,
        Saturday    = 5,
        Sunday      = 6,
    };

    /// Current year
    int16_t year{};
    /// Current month (1 = January)
    uint8_t month{};
    /// Day in month (starts at 1)
    uint8_t day{};

    /// Hour (0-23)
    uint8_t hour{};
    /// Minute (0-59)
    uint8_t minute{};
    /// Second (0-59)
    uint8_t second{};
    /// Subsecond fraction
    uint8_t subsecond{};

    Date() {};
    Date(const Date &old) : year(old.year), month(old.month), day(old.day), hour(old.hour),
        minute(old.minute), second(old.second), subsecond(old.subsecond) {}
    /// Create a date from an UNIX timestamp
    Date(const Timestamp unixTimestamp) {
        FromTimestamp(unixTimestamp, *this);
    }

    /// Convert this date to UNIX timestamp (without error checking)
    inline Timestamp toUnixTimestamp() const {
        Timestamp out{};
        ToTimestamp(*this, out);
        return out;
    }
    /// Convert this date to UNIX timestamp
    inline bool toUnixTimestamp(Timestamp &out) {
        return ToTimestamp(*this, out);
    }

    // Get weekday for this date
    inline Weekday getWeekday() const {
        Weekday out;
        GetWeekday(*this, out);
        return out;
    }

    /// Format date as an ISO 8601 string
    inline int toIso8601String(etl::span<char> buffer) const {
        return FormatIso8601String(*this, buffer);
    }
    /// Format date for use in HTTP protocol
    inline int toHttpDateString(etl::span<char> buffer) const {
        return FormatHttpString(*this, buffer);
    }

    static bool FromTimestamp(const Timestamp unixTimestamp, Date &out);
    static bool ToTimestamp(const Date &date, Timestamp &outTimestamp);
    static bool GetWeekday(const Date &date, Weekday &out);

    static int FormatIso8601String(const Date &date, etl::span<char> out);
    static int FormatHttpString(const Date &date, etl::span<char> out);
};
}

#endif
