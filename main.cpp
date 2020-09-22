#include "datetime.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace Test {

void runTest(DateTime &dt)
{
    std::cout << '\n';

    std::cout << "Current day: ";
    dt.getDate();

    std::cout << "Next day: ";
    dt.getNextDay();

    std::cout << "Previous day: ";
    dt.getPrevDay();
}

}; // namespace Test


namespace Fmt {

void refreshFile(std::ifstream& file)
{
    file.clear();
    file.seekg(0, file.beg);
}

size_t countLines(std::ifstream &file)
{
    int count = 0;

    for (std::string buffer; file; ++count) {
        std::getline(file, buffer);
    }

    Fmt::refreshFile(file);

    return count - 1;
}

std::string getString(const std::string &message)
{
    std::cout << message;

    std::string buffer;
    std::getline(std::cin, buffer);

    return buffer;
}

void openFile(std::ifstream &file, const std::string &message)
{
    do
    {
        file.open(Fmt::getString(message));
    }
    while (!file.is_open());
}

}; // namespace Fmt

int main()
{
    std::ifstream file;
    Fmt::openFile(file, "Type the filename: ");

    size_t lineCount = Fmt::countLines(file);
    std::vector<DateTime> dates(lineCount);

    std::string line;

    for (DateTime& date : dates) {
        std::getline(file, line);
        date.parseDate(line);
    }

    std::cout << "\nDates:\n";

    for (size_t i = 1, t = std::to_string(lineCount).length(); i <= lineCount; ++i) {
        std::cout << std::setfill(' ') << std::setw(t) << i << ". ";

        dates[i - 1].getDate();

        std::cout << ' ';
        dates[i - 1].getNextDay();

        std::cout << ' ';
        dates[i - 1].getPrevDay();

        std::cout << '\n';
    }

// ============================================================================

    std::cout << "\nDates with previous date in a previous year:\n";

    for (size_t i = 1, t = std::to_string(lineCount).length(); i <= lineCount; ++i) {
        if (dates[i - 1].day == FIRST_DAY && dates[i - 1].month == FIRST_MONTH) {
            if (dates[i - 1].year != FIRST_YEAR) {
                std::cout << std::setfill(' ') << std::setw(t) << i << ". ";

                dates[i - 1].getDate();

                std::cout << ' ';
                dates[i - 1].getPrevDay();

            }
            else {
                std::cout
                    << std::setfill(' ') << std::setw(t) << i
                    << ". 01.01.1970 31.12.1969";
            }
            std::cout << '\n';
        }
    }

// ============================================================================

    DateTime dateTimeNow = systemTime();

    std::cout << "\nCurrent system time: ";
    dateTimeNow.getFull();
    std::cout << '\n';

    return 0;
}
