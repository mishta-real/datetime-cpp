#include "datetime.hpp"

#include <fstream>
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

    for (size_t i = 1; i <= lineCount; ++i) {
        std::cout << i << ". ";

        dates[i - 1].getDate();

        std::cout << ' ';
        dates[i - 1].getNextDay();

        std::cout << ' ';
        dates[i - 1].getPrevDay();

        std::cout << '\n';
    }

    return 0;
}
