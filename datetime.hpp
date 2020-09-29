#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "timedelta.hpp"

#include <string>

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

constexpr int DAYS_IN_YEAR = 365;
constexpr int DAYS_IN_LEAP_YEAR = 366;

constexpr int HOURS_IN_DAY = 24;

constexpr int MINUTES_IN_HOUR = 60;
constexpr int MINUTES_IN_DAY = HOURS_IN_DAY * MINUTES_IN_HOUR;

constexpr int SECONDS_IN_MINUTE = 60;
constexpr int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * MINUTES_IN_HOUR;
constexpr int SECONDS_IN_DAY = SECONDS_IN_HOUR * HOURS_IN_DAY;
// constexpr int SECONDS_IN_28_DAYS = SECONDS_IN_DAY * 28;
// constexpr int SECONDS_IN_29_DAYS = SECONDS_IN_DAY * 29;
// constexpr int SECONDS_IN_30_DAYS = SECONDS_IN_DAY * 30;
// constexpr int SECONDS_IN_31_DAYS = SECONDS_IN_DAY * 31;
// constexpr int SECONDS_IN_MONTH = SECONDS_IN_DAY * DAYS_IN_MONTH_APPR;
constexpr int SECONDS_IN_YEAR = SECONDS_IN_DAY * DAYS_IN_YEAR;
constexpr int SECONDS_IN_LEAP_YEAR = SECONDS_IN_DAY * DAYS_IN_LEAP_YEAR;

constexpr int LEAP_DAY = DAYS_IN_LEAP_MONTH;

namespace DateTime {

struct DateTime {
    int day { FIRST_DAY };
    int month { FIRST_MONTH };
    int year { FIRST_YEAR };

    int hour { FIRST_HOUR };
    int minute { FIRST_MINUTE };
    int second { FIRST_SECOND };

    void getDate() const;
    void getTime() const;
    void getDateTime() const;

    // void getNextDay(DateTime &dt);
    void getNextDay() const;

    // void getPrevDay(DateTime &dt);
    void getPrevDay();

    TimeDelta::TimeDelta operator-(const DateTime &datetime2) const;

    DateTime operator+(const TimeDelta::TimeDelta &timedelta) const;
    DateTime operator-(const TimeDelta::TimeDelta &timedelta);
};

bool isYearLeap(const int t_year);

inline bool isDayCorrect(const int t_day, const int t_month, const int t_year);
inline bool isMonthCorrect(const int t_month);
inline bool isYearCorrect(const int t_year);

void dayIncorrectError(const int t_day);
void monthIncorrectError(const int t_month);
void yearIncorrectError(const int t_year);

void parseDate(const std::string &dateString, DateTime &date);

DateTime systemTime();

long long int dateToSeconds(const DateTime &dt);

void secondsToDate(const long long seconds, DateTime &dt);

} // namespace DateTime

#endif
