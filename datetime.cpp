#include "datetime.hpp"

#include <iomanip>
#include <iostream>


void DateTime::get()
{
    // Print the current day
    std::cout << std::setfill('0')
        << std::setw(2) << day << '.'
        << std::setw(2) << month << '.'
        << std::setw(4) << year << ' '
        << std::setw(2) << hour << ':'
        << std::setw(2) << minute << ':'
        << std::setw(2) << second << '\n';
}

inline bool DateTime::isYearLeap()
{
    return !(year % 4);
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
        << std::setw(4) << nextYear << '\n';
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
        << std::setw(4) << prevYear << '\n';
}
