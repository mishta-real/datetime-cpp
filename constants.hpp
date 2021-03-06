#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr int FIRST_YEAR = 1970;
constexpr int FIRST_MONTH = 1;
constexpr int FIRST_DAY = 1;

constexpr int FIRST_SECOND = 0;
constexpr int FIRST_MINUTE = 0;
constexpr int FIRST_HOUR = 0;

constexpr int MONTHS_IN_YEAR = 12;

constexpr int DAYS_IN_MONTH[MONTHS_IN_YEAR + 1] = {
    0,  // Needed to access Jan at index 1, not 0; Feb at index 2, not 1 etc.
    31, 28, 31,
    30, 31, 30,
    31, 31, 30,
    31, 30, 31
};

constexpr int DAYS_IN_LEAP_MONTH = 29;
constexpr double DAYS_IN_MONTH_APPR = 30.44;

constexpr int DAYS_IN_YEAR = 365;
constexpr int DAYS_IN_LEAP_YEAR = 366;

constexpr int HOURS_IN_DAY = 24;

constexpr int MINUTES_IN_HOUR = 60;
constexpr int MINUTES_IN_DAY = HOURS_IN_DAY * MINUTES_IN_HOUR;

constexpr int SECONDS_IN_MINUTE = 60;
constexpr int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * MINUTES_IN_HOUR;
constexpr int SECONDS_IN_DAY = SECONDS_IN_HOUR * HOURS_IN_DAY;
constexpr int SECONDS_IN_28_DAYS = SECONDS_IN_DAY * 28;
constexpr int SECONDS_IN_29_DAYS = SECONDS_IN_DAY * 29;
constexpr int SECONDS_IN_30_DAYS = SECONDS_IN_DAY * 30;
constexpr int SECONDS_IN_31_DAYS = SECONDS_IN_DAY * 31;
constexpr int SECONDS_IN_MONTH = SECONDS_IN_DAY * DAYS_IN_MONTH_APPR;
constexpr int SECONDS_IN_YEAR = SECONDS_IN_DAY * DAYS_IN_YEAR;
constexpr int SECONDS_IN_LEAP_YEAR = SECONDS_IN_DAY * DAYS_IN_LEAP_YEAR;

constexpr int LEAP_DAY = DAYS_IN_LEAP_MONTH;

#endif
