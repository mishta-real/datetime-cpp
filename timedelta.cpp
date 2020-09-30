#include "constants.hpp"
#include "datetime.hpp"
#include "timedelta.hpp"

#include <iostream>

namespace TimeDelta {

void TimeDelta::get()
{
    std::cout
        << years << " years, "
        << months << " months, "
        << days << " days, "
        << hours << " hours, "
        << minutes << " minutes, "
        << seconds << " seconds";

    if (years || months) {
        std::cout
            << "\nOR "
            << years * DAYS_IN_YEAR + months * 30 + days
            << " days, "
            << hours << " hours, "
            << minutes << " minutes, "
            << seconds << " seconds";

        if (years && months) {
            std::cout << " (1 year = 365 days, 1 month = 30 days)";
        }
        else if (years && !months) {
            std::cout << " (1 year = 365 days)";
        }
        else if (!years && months) {
            std::cout << " (1 month = 30 days)";
        }
    }
}

inline bool areYearsCorrect(const int t_years)
{
    return 0 <= t_years && t_years <= 99;
}

inline bool areMonthsCorrect(const int t_months)
{
    return 0 <= t_months && t_months <= 12;
}

inline bool areDaysCorrect(const int t_days)
{
    return 0 <= t_days && t_days <= 30;
}

inline bool areHoursCorrect(const int t_hours)
{
    return 0 <= t_hours && t_hours <= 23;
}

inline bool areMinutesCorrect(const int t_minutes)
{

    return 0 <= t_minutes && t_minutes <= 59;
}

inline bool areSecondsCorrect(const int t_seconds)
{
    return 0 <= t_seconds && t_seconds <= 59;
}

void daysIncorrectError(const int t_days)
{
    if (t_days > -1) {
        std::cerr << "Incorrect amount of days: " << t_days;
    }
    else {
        std::cerr << "Could not read the amount of days";
    }
    std::cout << std::endl;
    std::exit(1);
}

void monthsIncorrectError(const int t_months)
{
    if (t_months > -1) {
        std::cerr << "Incorrect amount of months: " << t_months;
    }
    else {
        std::cerr << "Could not read the amount of months";
    }
    std::cout << std::endl;
    std::exit(1);
}

void yearsIncorrectError(const int t_years)
{
    if (t_years > -1) {
        std::cerr << "Incorrect amount of years: " << t_years;
    }
    else {
        std::cerr << "Could not read the amount of years";
    }
    std::cout << std::endl;
    std::exit(1);
}

void hoursIncorrectError(const int t_hours)
{
    if (t_hours > -1) {
        std::cerr << "Incorrect amount of hours: " << t_hours;
    }
    else {
        std::cerr << "Could not read the amount of hours";
    }
    std::cout << std::endl;
    std::exit(1);
}

void minutesIncorrectError(const int t_minutes)
{
    if (t_minutes > -1) {
        std::cerr << "Incorrect amount of minutes: " << t_minutes;
    }
    else {
        std::cerr << "Could not read the amount of minutes";
    }
    std::cout << std::endl;
    std::exit(1);
}

void secondsIncorrectError(const int t_seconds)
{
    if (t_seconds > -1) {
        std::cerr << "Incorrect amount of seconds: " << t_seconds;
    }
    else {
        std::cerr << "Could not read the amount of seconds";
    }
    std::cout << std::endl;
    std::exit(1);
}

TimeDelta TimeDelta::operator+(const TimeDelta &timedelta2)
{
    const long long td1_seconds = timeDeltaToSeconds(*this);
    const long long td2_seconds = timeDeltaToSeconds(timedelta2);

    const long long td3_seconds = td1_seconds + td2_seconds;

    TimeDelta td3;
    secondsToTimeDelta(td3_seconds, td3);

    return td3;
}

TimeDelta TimeDelta::operator-(const TimeDelta &timedelta2)
{
    const long long td1_seconds = timeDeltaToSeconds(*this);
    const long long td2_seconds = timeDeltaToSeconds(timedelta2);

    const long long td3_seconds = td1_seconds > td2_seconds ?
        td1_seconds - td2_seconds :
        0;

    TimeDelta td3;
    secondsToTimeDelta(td3_seconds, td3);

    return td3;
}

void parseTimeDelta(const std::string &tdString, TimeDelta &td)
{
    // The only format is "yy mm dd hh:mm:ss"

    // Parsing the years
    int bufferYears = 0;
    if (std::isdigit(tdString[0]) && std::isdigit(tdString[1]))
    {
        bufferYears = (tdString[0] - '0') * 10 + (tdString[1] - '0');
    }
    else {
        yearsIncorrectError();
    }

    // Parsing the months
    int bufferMonths = 0;
    if (std::isdigit(tdString[3]) && std::isdigit(tdString[4])) {
        bufferMonths = (tdString[3] - '0') * 10 + (tdString[4] - '0');
    }
    else {
        monthsIncorrectError();
    }

    // Parsing the days
    int bufferDays = 0;
    if (std::isdigit(tdString[6]) && std::isdigit(tdString[7])) {
        bufferDays = (tdString[6] - '0') * 10 + (tdString[7] - '0');
    }
    else {
        daysIncorrectError();
    }

    // Checking the years
    if (areDaysCorrect(bufferDays)) {
        td.days = bufferDays;
    }
    else {
        daysIncorrectError(bufferDays);
    }

    // Checking the months
    if (areMonthsCorrect(bufferMonths)) {
        td.months = bufferMonths;
    }
    else {
        monthsIncorrectError(bufferMonths);
    }

    // Checking the days
    if (areYearsCorrect(bufferYears)) {
        td.years = bufferYears;
    }
    else {
        yearsIncorrectError(bufferYears);
    }

    // Parsing the hours
    if (std::isdigit(tdString[9]) && std::isdigit(tdString[10])) {
        int bufferHours = (tdString[9] - '0') * 10 + (tdString[10] - '0');

        if (areHoursCorrect(bufferHours)) {
            td.hours = bufferHours;
        }
        else {
            hoursIncorrectError(bufferHours);
        }
    }
    else {
        hoursIncorrectError();
    }

    // Parsing the minutes
    if (std::isdigit(tdString[12]) && std::isdigit(tdString[13])) {
        int bufferMinutes = (tdString[12] - '0') * 10 + (tdString[13] - '0');

        if (areMinutesCorrect(bufferMinutes)) {
            td.minutes = bufferMinutes;
        }
        else {
            minutesIncorrectError(bufferMinutes);
        }
    }
    else {
        minutesIncorrectError();
    }

    // Parsing the seconds
    if (std::isdigit(tdString[15]) && std::isdigit(tdString[16])) {
        int bufferSeconds = (tdString[15] - '0') * 10 + (tdString[16] - '0');

        if (areSecondsCorrect(bufferSeconds)) {
            td.seconds = bufferSeconds;
        }
        else {
            secondsIncorrectError(bufferSeconds);
        }
    }
    else {
        secondsIncorrectError();
    }
}

void secondsToTimeDelta(const long long t_seconds, TimeDelta &td)
{
    const long long time_seconds = t_seconds % SECONDS_IN_DAY;

    td.hours = time_seconds / SECONDS_IN_HOUR;
    td.minutes = time_seconds / MINUTES_IN_HOUR % SECONDS_IN_MINUTE;
    td.seconds = time_seconds % MINUTES_IN_HOUR;

    const long long date_seconds = t_seconds - time_seconds;

    // Assuming year has 365 days:
    td.years = date_seconds / SECONDS_IN_YEAR;
    // Assuming month has 30 days:
    td.months = (date_seconds % SECONDS_IN_YEAR) / SECONDS_IN_30_DAYS;
    td.days = ((date_seconds % SECONDS_IN_YEAR) % SECONDS_IN_30_DAYS) / SECONDS_IN_DAY;
}

long long timeDeltaToSeconds(const TimeDelta &td)
{
    const long long seconds = td.seconds
        + td.minutes * SECONDS_IN_MINUTE
        + td.hours * SECONDS_IN_HOUR
        + td.days * SECONDS_IN_DAY
        + td.months * SECONDS_IN_30_DAYS
        + td.years * SECONDS_IN_YEAR;

    return seconds;
}

} // namespace TimeDelta
