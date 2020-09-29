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

void parseTimeDelta(const std::string &tdString, TimeDelta &td);

void secondsToTimeDelta(const long long t_seconds, TimeDelta &td);
long long timeDeltaToSeconds(const TimeDelta &td);

} // namespace TimeDelta

#endif
