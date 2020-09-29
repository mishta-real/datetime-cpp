#include "datetime.hpp"
#include "timedelta.hpp"

#include <cmath>
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
            std::cout << "\n(1 year = 365 days, 1 month = 30 days)";
        }
        else if (years && !months) {
            std::cout << "\n(1 year = 365 days)";
        }
        else if (!years && months) {
            std::cout << "\n(1 month = 30 days)";
        }
    }
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

    // Parsing the year
    int bufferYears = 0;
    if (std::isdigit(tdString[0]) && std::isdigit(tdString[1]))
    {
        bufferYears = (tdString[0] - '0') * 10 + (tdString[1] - '0');
    }
    else {
        DateTime::yearIncorrectError(0);
    }

    // Parsing the month
    int bufferMonths = 0;
    if (std::isdigit(tdString[3]) && std::isdigit(tdString[4])) {
        bufferMonths = (tdString[3] - '0') * 10 + (tdString[4] - '0');
    }
    else {
        DateTime::monthIncorrectError(0);
    }

    // Parsing the day
    int bufferDays = 0;
    if (std::isdigit(tdString[6]) && std::isdigit(tdString[7])) {
        bufferDays = (tdString[6] - '0') * 10 + (tdString[7] - '0');
    }
    else {
        DateTime::dayIncorrectError(0);
    }

    if (DateTime::isDayCorrect(bufferDays, bufferMonths, bufferYears + FIRST_YEAR)) {
        td.days = bufferDays;
    }
    else {
        DateTime::dayIncorrectError(bufferDays);
    }

    if (DateTime::isMonthCorrect(bufferMonths)) {
        td.months = bufferMonths;
    }
    else {
        DateTime::monthIncorrectError(bufferMonths);
    }
    if (DateTime::isYearCorrect(FIRST_YEAR + bufferYears)) {
        td.years = bufferYears;
    }
    else {
        DateTime::yearIncorrectError(bufferYears + FIRST_YEAR);
    }

    // Parsing the hours
    if (std::isdigit(tdString[9]) && std::isdigit(tdString[10])) {
        int bufferHours = (tdString[9] - '0') * 10 + (tdString[10] - '0');

        if (DateTime::isHourCorrect(bufferHours)) {
            td.hours = bufferHours;
        }
        else {
            DateTime::hourIncorrectError(bufferHours);
        }
    }
    else {
        DateTime::hourIncorrectError(-1);
    }

    // Parsing the minutes
    if (std::isdigit(tdString[12]) && std::isdigit(tdString[13])) {
        int bufferMinutes = (tdString[12] - '0') * 10 + (tdString[13] - '0');

        if (DateTime::isMinuteCorrect(bufferMinutes)) {
            td.minutes = bufferMinutes;
        }
        else {
            DateTime::minuteIncorrectError(bufferMinutes);
        }
    }
    else {
        DateTime::minuteIncorrectError(-1);
    }

    // Parsing the seconds
    if (std::isdigit(tdString[15]) && std::isdigit(tdString[16])) {
        int bufferSeconds = (tdString[15] - '0') * 10 + (tdString[16] - '0');

        if (DateTime::isSecondCorrect(bufferSeconds)) {
            td.seconds = bufferSeconds;
        }
        else {
            DateTime::secondIncorrectError(bufferSeconds);
        }
    }
    else {
        DateTime::secondIncorrectError(-1);
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
