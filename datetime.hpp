#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

const int FIRST_YEAR = 1970;
const int FIRST_MONTH = 1;
const int FIRST_DAY = 1;

const int FIRST_SECOND = 0;
const int FIRST_MINUTE = 0;
const int FIRST_HOUR = 0;

const int SECONDS_IN_MINUTE = 60;
const int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * 60;
const int SECONDS_IN_DAY = SECONDS_IN_HOUR * 24;

const int SECONDS_IN_28_DAYS = SECONDS_IN_DAY * 28;
const int SECONDS_IN_29_DAYS = SECONDS_IN_DAY * 28;
const int SECONDS_IN_30_DAYS = SECONDS_IN_DAY * 30;
const int SECONDS_IN_31_DAYS = SECONDS_IN_DAY * 31;

const int SECONDS_IN_YEAR = SECONDS_IN_DAY * 365.25;

const int MONTHS_IN_YEAR = 12;

const int DAYS_IN_MONTH[MONTHS_IN_YEAR + 1] = {
    0,  // Needed to access Jan at index 1, not 0; Feb at index 2, not 1 etc.
    31, 28, 31,
    30, 31, 30,
    31, 31, 30,
    31, 30, 31
};

const int LEAP_DAY = 29;


struct DateTime {
    int day{ FIRST_DAY };
    int month{ FIRST_MONTH };
    int year{ FIRST_YEAR };

    int hour{ FIRST_HOUR };
    int minute{ FIRST_MINUTE };
    int second{ FIRST_SECOND };

    inline bool isYearLeap();

    void getFull();
    void getDate();
    void getTime();

    void getNextDay(DateTime &dt);
    void getNextDay();

    void getPrevDay(DateTime &dt);
    void getPrevDay();

    void parseDate(const std::string &line);
};

bool isYearLeap(const int t_year);

bool isDayCorrect(const int t_day, const int t_month, const int t_year);
bool isMonthCorrect(const int t_month);
bool isYearCorrect(const int t_year);

void dayIncorrectError(const int t_day);
void monthIncorrectError(const int t_month);
void yearIncorrectError(const int t_year);

DateTime systemTime();

#endif
