#include "datetime.hpp"

#include <iostream>

void runTest(DateTime &dt)
{
    std::cout << '\n';

    std::cout << "Current day: ";
    dt.get();

    std::cout << "Next day: ";
    dt.getNextDay();

    std::cout << "Previous day: ";
    dt.getPrevDay();
}

int main()
{
    DateTime dt1;
    runTest(dt1);

    DateTime dt2 = { 21, 9, 2020 };
    runTest(dt2);

    DateTime dt3 = { 1, 9, 2020 };
    runTest(dt3);

    // Previous day is leap
    DateTime dt4 = { 1, 3, 2020 };
    runTest(dt4);

    DateTime dt5 = { 1, 1, 2019 };
    runTest(dt5);

    DateTime dt6 = { 30, 9, 2020 };
    runTest(dt6);

    // Next day is leap
    DateTime dt7 = { 28, 2, 2020 };
    runTest(dt7);

    DateTime dt8 = { 31, 12, 2020 };
    runTest(dt8);

    return 0;
}
