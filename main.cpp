#include "datetime.hpp"
#include "timedelta.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


const std::string MENU(
    "1. Read dates from file" \
    "\n2. Read dates from file & get dates with previous days in previous years" \
    "\n3. Get system time" \
    "\n4. Date manipulation"
    "\n0. Exit\n"
);

enum tasks {
    T_1 = 1,
    T_2 = 2,
    T_3 = 3,
    T_4 = 4
};

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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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


namespace Task {

void task1()
{
    std::ifstream file;
    Fmt::openFile(file, "Type the filename: ");

    size_t lineCount = Fmt::countLines(file);
    std::vector<DateTime::DateTime> dates(lineCount);

    std::string line;

    for (DateTime::DateTime& date : dates) {
        std::getline(file, line);
        parseDateTime(line, date);
    }

    std::cout << "\nDates:\n";

    for (size_t i = 1, t = std::to_string(lineCount).length(); i <= lineCount; ++i) {
        std::cout << std::setfill(' ') << std::setw(t) << i << ".\t";

        dates[i - 1].getDate();

        std::cout << '\t';
        dates[i - 1].getNextDay();

        std::cout << '\t';
        dates[i - 1].getPrevDay();

        std::cout << '\n';
    }
}

void task2()
{
    std::ifstream file;
    Fmt::openFile(file, "Type the filename: ");

    size_t lineCount = Fmt::countLines(file);
    std::vector<DateTime::DateTime> dates(lineCount);

    std::string line;

    for (DateTime::DateTime &date : dates) {
        std::getline(file, line);
        parseDateTime(line, date);
    }

    std::cout << "\nDates with previous date in a previous year:\n";

    for (size_t i = 1, t = std::to_string(lineCount).length(); i <= lineCount; ++i)
    {
        if (dates[i - 1].day == FIRST_DAY && dates[i - 1].month == FIRST_MONTH)
        {
            if (dates[i - 1].year != FIRST_YEAR) {
                std::cout << std::setfill(' ') << std::setw(t) << i << ".\t";

                dates[i - 1].getDate();

                std::cout << '\t';
                dates[i - 1].getPrevDay();

            }
            else {
                std::cout
                    << std::setfill(' ') << std::setw(t) << i
                    << ".\t01.01.1970\t31.12.1969";
            }
            std::cout << '\n';
        }
    }
}

void task3()
{
    DateTime::DateTime dateTimeNow = DateTime::systemTime();

    std::cout << "\nCurrent system time: ";
    dateTimeNow.getDateTime();
    std::cout << '\n';
}

void task4()
{
    const std::string menu_t4 = "1. Calculate datetime difference" \
        "\n2. Add time period to a datetime" \
        "\n3. Sum two time periods" \
        "\n4. Substract two time periods" \
        "\n0. Return\n";

    int choice = 0;
    do {
        std::cout << menu_t4;

        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string dt_string = Fmt::getString("\nEnter the start datetime (dd.mm.yyyy hh:mm:ss): ");
            DateTime::DateTime dt_start;
            DateTime::parseDateTime(dt_string, dt_start);

            dt_string = Fmt::getString("\nEnter the end datetime (dd.mm.yyyy hh:mm:ss): ");
            DateTime::DateTime dt_end;
            DateTime::parseDateTime(dt_string, dt_end);

            std::cout << "\nStart datetime: ";
            dt_start.getDateTime();

            std::cout << "\nEnd datetime: ";
            dt_end.getDateTime();

            std::cout << "\n\nResult: ";
            TimeDelta::TimeDelta td = dt_end - dt_start;
            td.get();

            std::cout << "\n\n";
        }
        else if (choice == 2) {
            std::string dt1_string = Fmt::getString("\nEnter the datetime (dd.mm.yyyy hh:mm:ss): ");
            DateTime::DateTime dt1;
            DateTime::parseDateTime(dt1_string, dt1);

            std::string td_string = Fmt::getString("\nEnter time period (yy mm dd hh:mm:ss) (1y=365d, 1mo=30d): ");
            TimeDelta::TimeDelta td;
            TimeDelta::parseTimeDelta(td_string, td);

            std::cout << "\nDatetime: ";
            dt1.getDateTime();

            std::cout << "\n\nTime period: ";
            td.get();

            std::cout << "\n\nResult: ";
            DateTime::DateTime dt2 = dt1 + td;
            dt2.getDateTime();

            std::cout << "\n\n";
        }
        else if (choice == 3) {
            std::string td1_string = Fmt::getString("\nEnter the first time period (yy mm dd hh:mm:ss) (1y=365d, 1mo=30d): ");
            TimeDelta::TimeDelta td1;
            TimeDelta::parseTimeDelta(td1_string, td1);

            std::string td2_string = Fmt::getString("\nEnter the second time period (yy mm dd hh:mm:ss) (1y=365d, 1mo=30d): ");
            TimeDelta::TimeDelta td2;
            TimeDelta::parseTimeDelta(td2_string, td2);

            std::cout << "\nFirst time period: ";
            td1.get();

            std::cout << "\n\nSecond time period: ";
            td2.get();

            std::cout << "\n\nResult: ";
            TimeDelta::TimeDelta td3 = td1 + td2;
            td3.get();

            std::cout << "\n\n";
        }
        else if (choice == 4) {
            std::string td1_string = Fmt::getString("Enter the first time period (yy mm dd hh:mm:ss) (1y=365d, 1mo=30d): ");
            TimeDelta::TimeDelta td1;
            TimeDelta::parseTimeDelta(td1_string, td1);

            std::string td2_string = Fmt::getString("Enter the second time period (yy mm dd hh:mm:ss) (1y=365d, 1mo=30d): ");
            TimeDelta::TimeDelta td2;
            TimeDelta::parseTimeDelta(td2_string, td2);

            std::cout << "\nFirst time period: ";
            td1.get();

            std::cout << "\n\nSecond time period: ";
            td2.get();

            std::cout << "\n\nResult: ";
            TimeDelta::TimeDelta td3 = td1 - td2;
            td3.get();

            std::cout << "\n\n";
        }
    } while (choice == 1 || choice == 2 || choice == 3 || choice == 4);
}

}; // namespace Task

int askChoice()
{
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;

    return choice;
}

void menu()
{
    int choice;

    do {
        std::cout << MENU;

        switch (choice = askChoice()) {
        case T_1:
            std::cout << "\nTask 1.\n";
            Task::task1();
            std::cout << "\n\n";
            break;

        case T_2:
            std::cout << "\nTask 2.\n";
            Task::task2();
            std::cout << "\n\n";
            break;

        case T_3:
            std::cout << "\nTask 3.\n";
            Task::task3();
            std::cout << "\n\n";
            break;

        case T_4:
            std::cout << "\nTask 4.\n";
            Task::task4();
            std::cout << "\n\n";
            break;
        }
    } while (choice == T_1 || choice == T_2 || choice == T_3 || choice == T_4);
}
// ============================================================================

int main()
{
    menu();
    return 0;
}
