#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "constants.hpp"
#include "timedelta.hpp"

#include <string>

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

    TimeDelta::TimeDelta operator-(const DateTime &dt2) const;

    DateTime operator+(const TimeDelta::TimeDelta &td) const;
    DateTime operator-(const TimeDelta::TimeDelta &td);
};

inline bool isYearLeap(const int t_year);

inline bool isDayCorrect(const int t_day, const int t_month, const int t_year);
inline bool isMonthCorrect(const int t_month);
inline bool isYearCorrect(const int t_year);
inline bool isHourCorrect(const int t_hour);
inline bool isMinuteCorrect(const int t_minute);
inline bool isSecondCorrect(const int t_second);

void dayIncorrectError(const int t_day=0);
void monthIncorrectError(const int t_month=0);
void yearIncorrectError(const int t_year=0);
void hourIncorrectError(const int t_hour=-1);
void minuteIncorrectError(const int t_minute=-1);
void secondIncorrectError(const int t_second=-1);

void parseDateTime(const std::string &dtString, DateTime &dt);

DateTime systemTime();

long long int dateToSeconds(const DateTime &dt);

void secondsToDate(const long long seconds, DateTime &dt);

} // namespace DateTime

#endif
