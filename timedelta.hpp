#ifndef TIMEDELTA_HPP
#define TIMEDELTA_HPP

#include <string>

namespace TimeDelta {

struct TimeDelta {
    int days{ 0 };
    int months{ 0 };
    int years{ 0 };

    int hours{ 0 };
    int minutes{ 0 };
    int seconds{ 0 };

    void get();

    TimeDelta operator+(const TimeDelta &timedelta2);
    TimeDelta operator-(const TimeDelta &timedelta2);
};

inline bool areYearsCorrect(const int t_years);
inline bool areMonthsCorrect(const int t_months);
inline bool areDaysCorrect(const int t_days);
inline bool areHoursCorrect(const int t_hours);
inline bool areMinutesCorrect(const int t_minutes);
inline bool areSecondsCorrect(const int t_seconds);

void daysIncorrectError(const int t_days=-1);
void monthsIncorrectError(const int t_months=-1);
void yearsIncorrectError(const int t_years=-1);
void hoursIncorrectError(const int t_hours=-1);
void minutesIncorrectError(const int t_minutes=-1);
void secondsIncorrectError(const int t_seconds=-1);

void parseTimeDelta(const std::string &tdString, TimeDelta &td);

void secondsToTimeDelta(const long long t_seconds, TimeDelta &td);
long long timeDeltaToSeconds(const TimeDelta &td);

} // namespace TimeDelta

#endif
