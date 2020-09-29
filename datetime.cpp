#include "datetime.hpp"

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace DateTime {

bool isYearLeap(const int t_year)
{
    return
        ((t_year % 4 == 0) && (t_year % 100 != 0)) ||
        (t_year % 400 == 0);
}

bool areYearsCorrect(const int t_years)
{
    return 0 <= t_years && t_years <= 99;
}

bool isDayCorrect(const int t_day, const int t_month, const int t_year)
{
    if (!isYearLeap(t_year) || t_month != 2) {
        return FIRST_DAY <= t_day && t_day <= DAYS_IN_MONTH[t_month];
    }
    else {
        return FIRST_DAY <= t_day && t_day <= LEAP_DAY;
    }
}

bool isMonthCorrect(const int t_month)
{
    return FIRST_MONTH <= t_month && t_month <= MONTHS_IN_YEAR;
}

bool isYearCorrect(const int t_year)
{
    return FIRST_YEAR <= t_year;
}

bool isHourCorrect(const int t_hour)
{
    return 0 <= t_hour && t_hour <= 23;
}

bool isMinuteCorrect(const int t_minute)
{

    return 0 <= t_minute && t_minute <= 59;
}

bool isSecondCorrect(const int t_second)
{
    return 0 <= t_second && t_second <= 59;
}

void dayIncorrectError(const int t_day=0)
{
    if (t_day) {
        std::cerr << "Incorrect day " << t_day;
    }
    else {
        std::cerr << "Could not read the day";
    }
    std::cout << std::endl;
    std::exit(1);
}

void monthIncorrectError(const int t_month=0)
{
    if (t_month) {
        std::cerr << "Incorrect month " << t_month;
    }
    else {
        std::cerr << "Could not read the month";
    }
    std::cout << std::endl;
    std::exit(1);
}

void yearIncorrectError(const int t_year=0)
{
    if (t_year) {
        std::cerr << "Incorrect year " << t_year;
    }
    else {
        std::cerr << "Could not read the year";
    }
    std::cout << std::endl;
    std::exit(1);
}

void hourIncorrectError(const int t_hour=-1)
{
    if (t_hour != -1) {
        std::cerr << "Incorrect hour " << t_hour;
    }
    else {
        std::cerr << "Could not read the hours";
    }
    std::cout << std::endl;
    std::exit(1);

}

void minuteIncorrectError(const int t_minute=-1)
{
    if (t_minute != -1) {
        std::cerr << "Incorrect minute " << t_minute;
    }
    else {
        std::cerr << "Could not read the minutes";
    }
    std::cout << std::endl;
    std::exit(1);
}

void secondIncorrectError(const int t_second=-1)
{
    if (t_second != -1) {
        std::cerr << "Incorrect second " << t_second;
    }
    else {
        std::cerr << "Could not read the seconds";
    }
    std::cout << std::endl;
    std::exit(1);
}

// Print date & time
void DateTime::getDateTime() const
{
    std::cout <<
        std::setfill('0') <<
        std::setw(2) << day << '.' <<
        std::setw(2) << month << '.' <<
        std::setw(4) << year << ' ' <<
        std::setw(2) << hour << ':' <<
        std::setw(2) << minute << ':' <<
        std::setw(2) << second;
}

// Print date
void DateTime::getDate() const
{
    std::cout <<
        std::setfill('0') <<
        std::setw(2) << day << '.' <<
        std::setw(2) << month << '.' <<
        std::setw(4) << year;
}

// Print time
void DateTime::getTime() const
{
    std::cout <<
        std::setfill('0') <<
        std::setw(2) << hour << ':' <<
        std::setw(2) << minute << ':' <<
        std::setw(2) << second;
}

void DateTime::getNextDay() const
{
    int nextDay = day + 1;
    int nextMonth = month;

    if (!isYearLeap(year)) {
        if (nextDay > DAYS_IN_MONTH[month]) {
            nextDay = 1;
            ++nextMonth;
        }
    }
    else {
        if ((month != 2 && nextDay > DAYS_IN_MONTH[month]) ||
            (month == 2 && nextDay > LEAP_DAY))
        {
            nextDay = 1;
            ++nextMonth;
        }
    }

    int nextYear = year;

    if (nextMonth > MONTHS_IN_YEAR) {
        nextMonth = 1;
        ++nextYear;
    }

    std::cout <<
        std::setfill('0') <<
        std::setw(2) << nextDay << '.' <<
        std::setw(2) << nextMonth << '.' <<
        std::setw(4) << nextYear;
}

void DateTime::getPrevDay()
{
    int prevDay = day;
    int prevMonth = month;
    int prevYear = year;

    // If date is not 01.01.1970:
    if (year != FIRST_YEAR || month != FIRST_MONTH || day != FIRST_DAY) {
        prevDay -= 1;

        if (prevDay >= FIRST_DAY) {
            // None
        }
        // If day is 0 we change the month and then the day and even the year:
        else {
            prevMonth -= 1;

            if (isYearLeap(year) && prevMonth == 2) {
                // Feb 29:
                prevDay = LEAP_DAY;
            }
            else if (prevMonth >= FIRST_MONTH) {
                prevDay = DAYS_IN_MONTH[prevMonth]; // Last day of the month
            }
            else {
                prevYear -= 1;
                // Dec 31:
                prevMonth = 12;
                prevDay = DAYS_IN_MONTH[prevMonth];
            }
        }
    }

    std::cout <<
        std::setfill('0') <<
        std::setw(2) << prevDay << '.' <<
        std::setw(2) << prevMonth << '.' <<
        std::setw(4) << prevYear;
}

TimeDelta::TimeDelta DateTime::operator-(const DateTime &dt2) const
{
    const long long dt1_seconds = dateToSeconds(*this);
    const long long dt2_seconds = dateToSeconds(dt2);

    const long long td_seconds = std::abs(dt1_seconds - dt2_seconds);

    TimeDelta::TimeDelta td;
    TimeDelta::secondsToTimeDelta(td_seconds, td);
    return td;
}

DateTime DateTime::operator+(const TimeDelta::TimeDelta &td) const
{
    const long long dt1_seconds = dateToSeconds(*this);
    const long long td_seconds = TimeDelta::timeDeltaToSeconds(td);

    const long long dt2_seconds = dt1_seconds + td_seconds;

    DateTime dt2;
    secondsToDate(dt2_seconds, dt2);
    return dt2;
}

DateTime DateTime::operator-(const TimeDelta::TimeDelta &td)
{
    const long long dt1_seconds = dateToSeconds(*this);
    const long long td_seconds = TimeDelta::timeDeltaToSeconds(td);

    const long long dt2_seconds = dt1_seconds > td_seconds ? dt1_seconds - td_seconds : 0;

    DateTime dt2;
    if (dt2_seconds) {
        secondsToDate(dt2_seconds, dt2);
    }
    else {
        dt2 = {
            FIRST_DAY, FIRST_MONTH, FIRST_YEAR,
            FIRST_HOUR, FIRST_MINUTE, FIRST_SECOND
        };
    }
    return dt2;
}

void parseDateTime(const std::string &dtString, DateTime &dt)
{
    // The only format is "dd.mm.yyyy hh:mm:ss"

    // Parsing the day
    int bufferDay = 0;
    if (std::isdigit(dtString[0]) && std::isdigit(dtString[1])) {
        bufferDay = (dtString[0] - '0') * 10 + (dtString[1] - '0');
    }
    else {
        dayIncorrectError();
    }

    // Parsing the month
    int bufferMonth = 0;
    if (std::isdigit(dtString[3]) && std::isdigit(dtString[4])) {
        bufferMonth = (dtString[3] - '0') * 10 + (dtString[4] - '0');
    }
    else {
        monthIncorrectError();
    }

    // Parsing the year
    int bufferYear = 0;
    if (std::isdigit(dtString[6]) && std::isdigit(dtString[7])
        && std::isdigit(dtString[8]) && std::isdigit(dtString[9]))
    {
        bufferYear = (dtString[6] - '0') * 1000
            + (dtString[7] - '0') * 100
            + (dtString[8] - '0') * 10
            + (dtString[9] - '0');
    }
    else {
        yearIncorrectError();
    }

    // Checking the day
    if (isDayCorrect(bufferDay, bufferMonth, bufferYear)) {
        dt.day = bufferDay;
    }
    else {
        dayIncorrectError(bufferDay);
    }

    // Checking the month
    if (isMonthCorrect(bufferMonth)) {
        dt.month = bufferMonth;
    }
    else {
        monthIncorrectError(bufferMonth);
    }

    // Checking the year
    if (isYearCorrect(bufferYear)) {
        dt.year = bufferYear;
    }
    else {
        yearIncorrectError(bufferYear);
    }

    // Parsing the hour
    if (std::isdigit(dtString[11]) && std::isdigit(dtString[12]))
    {
        int bufferHour = (dtString[11] - '0') * 10 + (dtString[12] - '0');

        if (isHourCorrect(bufferHour)) {
            dt.hour = bufferHour;
        }
        else {
            hourIncorrectError(bufferHour);
        }
    }
    else {
        hourIncorrectError();
    }

    // Parsing the minutes
    if (std::isdigit(dtString[14]) && std::isdigit(dtString[15])) {
        int bufferMinute = (dtString[14] - '0') * 10 + (dtString[15] - '0');

        if (isMinuteCorrect(bufferMinute)) {
            dt.minute = bufferMinute;
        }
        else {
            minuteIncorrectError(bufferMinute);
        }
    }
    else {
        minuteIncorrectError();
    }

    // Parsing the seconds
    if (std::isdigit(dtString[17]) && std::isdigit(dtString[18])) {
        int bufferSecond = (dtString[17] - '0') * 10 + (dtString[18] - '0');

        if (isSecondCorrect(bufferSecond)) {
            dt.second = bufferSecond;
        }
        else {
            secondIncorrectError(bufferSecond);
        }
    }
    else {
        secondIncorrectError();
    }
}


DateTime systemTime()
{
    time_t t = std::time(0);
    tm *now = std::localtime(&t);

    DateTime sysTime = {
        now->tm_mday,
        now->tm_mon + 1,
        now->tm_year + 1900,
        now->tm_hour,
        now->tm_min,
        now->tm_sec
    };

    return sysTime;
}

// Get date since epoch in seconds
long long int dateToSeconds(const DateTime &dt)
{
    const long long time_seconds = dt.second
        + dt.minute * SECONDS_IN_MINUTE
        + dt.hour * SECONDS_IN_HOUR;

    long long date_seconds = (dt.day - 1) * SECONDS_IN_DAY;

    for (int t_month = dt.month - 1; t_month >= FIRST_MONTH; --t_month)
    {
        if (!isYearLeap(dt.year) || t_month != 2) {
            date_seconds += DAYS_IN_MONTH[t_month] * SECONDS_IN_DAY;
        }
        else {
            date_seconds += DAYS_IN_LEAP_MONTH * SECONDS_IN_DAY;
        }
    }

    for (int t_year = dt.year - 1; t_year >= FIRST_YEAR; --t_year)
    {
        if (!isYearLeap(t_year)) {
            date_seconds += DAYS_IN_YEAR * SECONDS_IN_DAY;
        }
        else {
            date_seconds += DAYS_IN_LEAP_YEAR * SECONDS_IN_DAY;
        }
    }

    return date_seconds + time_seconds;
}
/*    long long int seconds = dt.second
        + dt.minute * SECONDS_IN_MINUTE
        + dt.hour * SECONDS_IN_HOUR
        + (dt.day - 1) * SECONDS_IN_DAY;

    for (int t_month = dt.month - 1; t_month >= FIRST_MONTH; --t_month) {
        if (!isYearLeap(dt.year) || t_month != 2) {
            seconds += DAYS_IN_MONTH[t_month] * SECONDS_IN_DAY;
        }
        else {
            seconds += DAYS_IN_LEAP_MONTH * SECONDS_IN_DAY;
        }
    }

    for (int t_year = dt.year - 1; t_year >= FIRST_YEAR; --t_year) {
        if (!isYearLeap(t_year)) {
            seconds += DAYS_IN_YEAR * SECONDS_IN_DAY;
        }
        else {
            seconds += DAYS_IN_LEAP_YEAR * SECONDS_IN_DAY;
        }
    }

    return seconds;
} */

// Get date since epoch in normal format
void secondsToDate(const long long seconds, DateTime &dt)
{
    const int time_seconds = seconds % SECONDS_IN_DAY;
    dt.hour = time_seconds / SECONDS_IN_HOUR;
    dt.minute = time_seconds / MINUTES_IN_HOUR % SECONDS_IN_MINUTE;
    dt.second = time_seconds % SECONDS_IN_MINUTE;

    int date_seconds = seconds - time_seconds;

    int years = 0;
    for (int y = years + FIRST_YEAR;
        date_seconds > SECONDS_IN_YEAR;
        ++y, ++years)
    {
        if (!isYearLeap(y)) {
            date_seconds -= SECONDS_IN_YEAR;
        }
        else {
            date_seconds -= SECONDS_IN_LEAP_YEAR;
        }
    }

    dt.year = FIRST_YEAR + years;

    int months = 0;
    for (int m = 1;
        date_seconds > DAYS_IN_MONTH[m] * SECONDS_IN_DAY;
        ++m, ++months)
    {
        if (!isYearLeap(dt.year) || m != 2) {
            date_seconds -= DAYS_IN_MONTH[m] * SECONDS_IN_DAY;
        }
        else {
            date_seconds -= DAYS_IN_LEAP_MONTH * SECONDS_IN_DAY;
        }
    }

    dt.month = months + 1;

    const int days = date_seconds / SECONDS_IN_DAY + 1;

    if (days <= DAYS_IN_MONTH[dt.month] || (isYearLeap(dt.year) && dt.month == 2)) {
        dt.day = days;
    }
    else {
        dt.day = FIRST_DAY;
        ++dt.month;
        if (dt.month > MONTHS_IN_YEAR) {
            dt.month = FIRST_MONTH;
            ++dt.year;
        }
    }
}

} // namespace DateTime
