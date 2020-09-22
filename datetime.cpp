#include "datetime.hpp"

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>

inline bool DateTime::isYearLeap()
{
    return !(year % 4);
}

inline bool isYearLeap(const int t_year)
{
    return !(t_year % 4);
}

void DateTime::getFull()
{
    // Print the current date & time
    std::cout << std::setfill('0')
        << std::setw(2) << day << '.'
        << std::setw(2) << month << '.'
        << std::setw(4) << year << ' '
        << std::setw(2) << hour << ':'
        << std::setw(2) << minute << ':'
        << std::setw(2) << second;
}

void DateTime::getDate()
{
    // Print the current date
    std::cout << std::setfill('0')
        << std::setw(2) << day << '.'
        << std::setw(2) << month << '.'
        << std::setw(4) << year;
}

void DateTime::getTime()
{
    // Print the current time
    std::cout << std::setfill('0')
        << std::setw(2) << hour << ':'
        << std::setw(2) << minute << ':'
        << std::setw(2) << second;
}

// The next day will be assigned to dt
void DateTime::getNextDay(DateTime &dt)
{
    int nextDay = day + 1;
    int nextMonth = month;

    if (nextDay > DAYS_IN_MONTH[month]) {
        // Not February or not a leap year condition:
        if (!isYearLeap() || month != 2) {
            nextDay = 1;
            ++nextMonth;
        }
        // February 29th case:
        else {
            // None
        }
    }

    int nextYear = year;

    if (nextMonth > MONTHS_IN_YEAR) {
        nextMonth = 1;
        ++nextYear;
    }

    dt = { nextDay, nextMonth, nextYear };
}

void DateTime::getNextDay()
{
    int nextDay = day + 1;
    int nextMonth = month;

    if (nextDay > DAYS_IN_MONTH[month]) {
        // Not february or not a leap year condition:
        if (!isYearLeap() || month != 2) {
            nextDay = 1;
            ++nextMonth;
        }
        // February 29th case:
        else {
            // None
        }
    }

    int nextYear = year;

    if (nextMonth > MONTHS_IN_YEAR) {
        nextMonth = 1;
        ++nextYear;
    }

    std::cout << std::setfill('0')
        << std::setw(2) << nextDay << '.'
        << std::setw(2) << nextMonth << '.'
        << std::setw(4) << nextYear;
}

// The previous day will be assigned to dt
void DateTime::getPrevDay(DateTime &dt)
{
    int prevDay = day;
    int prevMonth = month;
    int prevYear = year;

    if (year != FIRST_YEAR || month != FIRST_MONTH || day != FIRST_DAY)
    {
        --prevDay;

        if (prevDay > 0) {
            // None
        }
        else {
            --prevMonth;

            if (isYearLeap() && prevMonth == 2) {
                prevDay = LEAP_DAY;
            }
            else if (prevMonth >= FIRST_MONTH) {
                prevDay = DAYS_IN_MONTH[prevMonth];
            }
            else {
                --prevYear;
                prevMonth = 12;
                prevDay = DAYS_IN_MONTH[prevMonth];
            }
        }
    }
    else {
        // The first day - do nothing
    }

    dt = { prevDay, prevMonth, prevYear };
}

void DateTime::getPrevDay()
{
    int prevDay = day;
    int prevMonth = month;
    int prevYear = year;

    if (year != FIRST_YEAR || month != FIRST_MONTH || day != FIRST_DAY)
    {
        --prevDay;

        if (prevDay > 0) {
            // None
        }
        else {
            --prevMonth;

            if (isYearLeap() && prevMonth == 2) {
                prevDay = LEAP_DAY;
            }
            else if (prevMonth >= FIRST_MONTH) {
                prevDay = DAYS_IN_MONTH[prevMonth];
            }
            else {
                --prevYear;
                prevMonth = 12;
                prevDay = DAYS_IN_MONTH[prevMonth];
            }
        }
    }
    else {
        // The first day - do nothing
    }

    std::cout << std::setfill('0')
        << std::setw(2) << prevDay << '.'
        << std::setw(2) << prevMonth << '.'
        << std::setw(4) << prevYear;
}

void DateTime::parseDate(const std::string &line)
{
    // The only format is "DD.MM.YYYY"

    // Parsing the day
    if (std::isdigit(line[0]) && std::isdigit(line[1])) {
        int bufferDay = (line[0] - '0') * 10 + line[1] - '0';
        if (isDayCorrect(bufferDay, month, year)) {
            day = bufferDay;    // Adding day
        }
        else {
            dayIncorrectError(bufferDay);
        }
    }
    else {
        dayIncorrectError(0);
    }

    // Parsing the month
    if (std::isdigit(line[3]) && std::isdigit(line[4])) {
        int bufferMonth = (line[3] - '0') * 10 + line[4] - '0';
        if (isMonthCorrect(bufferMonth)) {
            month = bufferMonth;    // Adding month
        }
        else {
            monthIncorrectError(bufferMonth);
        }
    }
    else {
        monthIncorrectError(0);
    }

    // Parsing the year
    if (std::isdigit(line[6]) && std::isdigit(line[7])
        && std::isdigit(line[8]) && std::isdigit(line[9]))
    {
        int bufferYear = (line[6] - '0') * 1000
            + (line[7] - '0') * 100
            + (line[8] - '0') * 10
            + line[9] - '0';
        if (isYearCorrect(bufferYear)) {
            year = bufferYear;  // Adding year
        }
        else {
            yearIncorrectError(bufferYear);
        }
    }
    else {
        yearIncorrectError(0);
    }
}

bool isDayCorrect(const int t_day, const int t_month, const int t_year)
{
    return FIRST_DAY <= t_day && (t_day <= DAYS_IN_MONTH[t_month] ||
         (isYearLeap(t_year) &&
         t_month == 2 &&
         t_day <= LEAP_DAY));
}

bool isMonthCorrect(const int t_month)
{
    return FIRST_MONTH <= t_month && t_month <= MONTHS_IN_YEAR;
}

bool isYearCorrect(const int t_year)
{
    return FIRST_YEAR <= t_year;
}

void dayIncorrectError(const int t_day=0)
{
    if (t_day) {
        std::cerr << "Incorrect day " << t_day;
    }
    else {
        std::cerr << "Given day is incorrect";
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
        std::cerr << "Given month is incorrect";
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
        std::cerr << "Given year is incorrect";
    }
    std::cout << std::endl;
    std::exit(1);
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
