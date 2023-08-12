#include <limits.h>
#include <etl/array.h>
#include <printf/printf.h>

#include "Util/Date.h"

namespace Util {
/**
 * @brief Map of month name -> short name
 */
static const etl::array<const char *, 12> gMonthShortNames{{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
}};

/**
 * @brief Map of weekday index -> short name
 */
static const etl::array<const char *, 7> gWeekdayShortNames{{
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
}};
}

using namespace Util;

/* 2000-03-01 (mod 400 year, immediately after feb29 */
#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

/**
 * @brief Convert the specified UNIX timestamp to a date
 *
 * Based on [musl libc](http://git.musl-libc.org/cgit/musl/tree/src/time/__secs_to_tm.c?h=v0.9.15)
 * code.
 */
bool Date::FromTimestamp(const Timestamp t, Date &out) {
    long long days, secs;
    int remdays, remsecs, remyears;
    int qc_cycles, c_cycles, q_cycles;
    int years, months;
    int wday, yday, leap;
    static const char days_in_month[] = {31,30,31,30,31,31,30,31,30,31,31,29};

    // Reject time_t values whose year would overflow int
    if(static_cast<long long>(t) < INT_MIN * 31622400LL ||
            static_cast<long long>(t) > INT_MAX * 31622400LL) {
        return false;
    }

    secs = t - LEAPOCH;
    days = secs / 86400;
    remsecs = secs % 86400;
    if(remsecs < 0) {
        remsecs += 86400;
        days--;
    }

    wday = (3+days) % 7;
    if(wday < 0) wday += 7;

    qc_cycles = days / DAYS_PER_400Y;
    remdays = days % DAYS_PER_400Y;
    if(remdays < 0) {
        remdays += DAYS_PER_400Y;
        qc_cycles--;
    }

    c_cycles = remdays / DAYS_PER_100Y;
    if(c_cycles == 4) c_cycles--;
    remdays -= c_cycles * DAYS_PER_100Y;

    q_cycles = remdays / DAYS_PER_4Y;
    if(q_cycles == 25) q_cycles--;
    remdays -= q_cycles * DAYS_PER_4Y;

    remyears = remdays / 365;
    if(remyears == 4) remyears--;
    remdays -= remyears * 365;

    leap = !remyears && (q_cycles || !c_cycles);
    yday = remdays + 31 + 28 + leap;
    if(yday >= 365+leap) yday -= 365+leap;

    years = remyears + 4*q_cycles + 100*c_cycles + 400*qc_cycles;

    for(months=0; days_in_month[months] <= remdays; months++) {
        remdays -= days_in_month[months];
    }

    if(years+100 > INT_MAX || years+100 < INT_MIN) {
        return false;
    }

    out.year = (years + 100) + 1900;
    out.month = months + 2;
    if(out.month >= 12) {
        out.month -= 12;
        out.year++;
    }
    out.month++;
    out.day = remdays + 1;
    // TODO: do we want/need to store these?
    //tm->tm_wday = wday;
    //tm->tm_yday = yday;

    out.hour = remsecs / 3600;
    out.minute = remsecs / 60 % 60;
    out.second = remsecs % 60;

    return true;
}

/**
 * @brief Convert the date to an UNIX timestamp
 *
 * @remark Keep in mind UNIX timestamps can only represent dates between January 1, 1970 and
 *         January 19, 2038 when the 32-bit value overflows.
 */
bool Date::ToTimestamp(const Date &date, Timestamp &outTimestamp) {
    // based on: https://github.com/protocolbuffers/upb/blob/22182e6e/upb/json_decode.c#L982
    const uint32_t year_base = 4800;    /* Before min year, multiple of 400. */
    const uint32_t m_adj = date.month - 3;       /* March-based month. */
    const uint32_t carry = m_adj > date.month ? 1 : 0;
    const uint32_t adjust = carry ? 12 : 0;
    const uint32_t y_adj = date.year + year_base - carry;
    const uint32_t month_days = ((m_adj + adjust) * 62719 + 769) / 2048;
    const uint32_t leap_days = y_adj / 4 - y_adj / 100 + y_adj / 400;
    outTimestamp = (y_adj * 365 + leap_days + month_days + (date.day - 1) - 2472632) +
        (date.hour * 3600) + (date.minute * 60) + date.second;
    return true;
}

/**
 * @brief Get the weekday this date corresponds to
 */
bool Date::GetWeekday(const Date &date, Weekday &out) {
    int y = date.year, m = date.month, d = date.day;
    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;

    switch(weekday) {
        case 0:
            out = Weekday::Sunday;
            break;
        case 1:
            out = Weekday::Monday;
            break;
        case 2:
            out = Weekday::Tuesday;
            break;
        case 3:
            out = Weekday::Wednesday;
            break;
        case 4:
            out = Weekday::Thursday;
            break;
        case 5:
            out = Weekday::Friday;
            break;
        case 6:
            out = Weekday::Saturday;
            break;
        default:
            return false;
    }

    return true;
}


/**
 * @brief Convert date to string (ISO 8601 format)
 */
int Date::FormatIso8601String(const Date &date, etl::span<char> out) {
    return snprintf(out.data(), out.size(), "%04d-%02d-%02dT%02d:%02d:%02dZ", date.year, date.month,
            date.day, date.hour, date.minute, date.second);
}

/**
 * @brief Convert date to string (HTTP header format)
 */
int Date::FormatHttpString(const Date &date, etl::span<char> out) {
    return snprintf(out.data(), out.size(), "%s, %02d %s %4d %02d:%02d:%02d GMT",
            gWeekdayShortNames[static_cast<size_t>(date.getWeekday())], date.day,
            gMonthShortNames[date.month - 1], date.year, date.hour, date.minute, date.second);
}
