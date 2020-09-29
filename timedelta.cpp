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
        << seconds << " seconds.";
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

void secondsToTimeDelta(const long long t_seconds, TimeDelta &td)
{
    DateTime::DateTime dt;
    DateTime::secondsToDate(t_seconds, dt);

    td = {
        dt.day - FIRST_DAY,
        dt.month - FIRST_MONTH,
        dt.year - FIRST_YEAR,
        dt.hour - FIRST_HOUR,
        dt.minute - FIRST_MINUTE,
        dt.second - FIRST_SECOND
    };
}


long long timeDeltaToSeconds(const TimeDelta &td)
{
    DateTime::DateTime dt = {
        FIRST_DAY + td.days,
        FIRST_MONTH + td.months,
        FIRST_YEAR + td.years,
        FIRST_HOUR + td.hours,
        FIRST_MINUTE + td.minutes,
        FIRST_SECOND + td.seconds
    };

    return DateTime::dateToSeconds(dt);
}

} // namespace TimeDelta
