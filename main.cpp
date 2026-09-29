// main.cpp
// Interaction layer - Coding B (MohammadHossein)
//
// Responsibilities:
//   - Main menu and navigation
//   - Reading and validating user input
//   - Calling the core logic (Coding A, see logic.h)
//   - Displaying results
//   - Repeat / Exit behaviour
//
// Build: g++ -std=c++17 -Wall -Wextra -pedantic -o program main.cpp logic.cpp

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "logic.h"

// ---------------------------------------------------------------
// Program text (update once the Part 1 technology is confirmed)
// ---------------------------------------------------------------
const std::string PROGRAM_TITLE = "PROGRAM NAME";          // TODO: e.g. "NETFLIX MOVIE ASSISTANT"
const std::string FEATURE_NAME  = "Run Main Feature";      // TODO: e.g. "Get a Movie Recommendation"
const std::string ABOUT_TEXT    =
    "This program is connected to the technology studied in Part 1.\n"
    "TODO: describe the technology and what this program simulates.";

const int MENU_MAIN_FEATURE = 1;
const int MENU_ABOUT        = 2;
const int MENU_EXIT         = 3;

// ---------------------------------------------------------------
// Input helpers
// ---------------------------------------------------------------

// Removes spaces and tabs from both ends of the text.
std::string trim(const std::string& text)
{
    const std::string whitespace = " \t\r\n";
    const std::size_t start = text.find_first_not_of(whitespace);
    if (start == std::string::npos)
    {
        return "";
    }
    const std::size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

// Reads one full line. If input has ended (Ctrl+Z / Ctrl+D or end of a
// piped file), the program exits cleanly instead of looping forever.
std::string readLineOrExit()
{
    std::string line;
    if (!std::getline(std::cin, line))
    {
        std::cout << "\n\nNo more input detected. Exiting the program. Goodbye!\n";
        std::exit(0);
    }
    return trim(line);
}

// Asks until the user enters a whole number between minValue and maxValue.
// Rejects empty input, text ("abc"), mixed input ("12abc") and decimals ("3.5").
int readIntInRange(const std::string& prompt, int minValue, int maxValue)
{
    while (true)
    {
        std::cout << prompt;
        const std::string userInput = readLineOrExit();

        if (userInput.empty())
        {
            std::cout << "Input cannot be empty. Please try again.\n\n";
            continue;
        }

        int number = 0;
        std::size_t charactersRead = 0;
        try
        {
            number = std::stoi(userInput, &charactersRead);
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a valid whole number.\n\n";
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "That number is too large. Please enter a number between "
                      << minValue << " and " << maxValue << ".\n\n";
            continue;
        }

        if (charactersRead != userInput.size())
        {
            std::cout << "Invalid input. Please enter a valid whole number.\n\n";
            continue;
        }

        if (number < minValue || number > maxValue)
        {
            std::cout << "Value out of range. Please enter a number between "
                      << minValue << " and " << maxValue << ".\n\n";
            continue;
        }

        return number;
    }
}

// Asks until the user enters a number (decimals allowed) between minValue and maxValue.
double readDoubleInRange(const std::string& prompt, double minValue, double maxValue)
{
    while (true)
    {
        std::cout << prompt;
        const std::string userInput = readLineOrExit();

        if (userInput.empty())
        {
            std::cout << "Input cannot be empty. Please try again.\n\n";
            continue;
        }

        double number = 0.0;
        std::size_t charactersRead = 0;
        try
        {
            number = std::stod(userInput, &charactersRead);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid input. Please enter a valid number.\n\n";
            continue;
        }

        // Reject leftovers like "12abc" and special values like "nan" or "inf".
        if (charactersRead != userInput.size() || !std::isfinite(number))
        {
            std::cout << "Invalid input. Please enter a valid number.\n\n";
            continue;
        }

        if (number < minValue || number > maxValue)
        {
            std::cout << "Value out of range. Please enter a number between "
                      << minValue << " and " << maxValue << ".\n\n";
            continue;
        }

        return number;
    }
}

// ---------------------------------------------------------------
// Output helpers
// ---------------------------------------------------------------

void printDivider()
{
    std::cout << "=================================================\n";
}

void showMainMenu()
{
    std::cout << "\n";
    printDivider();
    std::cout << "   " << PROGRAM_TITLE << "\n";
    printDivider();
    std::cout << "  " << MENU_MAIN_FEATURE << ". " << FEATURE_NAME << "\n";
    std::cout << "  " << MENU_ABOUT        << ". About this program\n";
    std::cout << "  " << MENU_EXIT         << ". Exit\n";
    printDivider();
}

void showAbout()
{
    std::cout << "\n--------------- ABOUT ---------------\n";
    std::cout << ABOUT_TEXT << "\n";
    std::cout << "-------------------------------------\n";
}

void displayResult(const std::string& result)
{
    std::cout << "\n------------------ RESULT ------------------\n";
    std::cout << result << "\n";
    std::cout << "--------------------------------------------\n";
}

// ---------------------------------------------------------------
// Main feature: get input -> validate -> call core logic -> display
// ---------------------------------------------------------------

void runMainFeature()
{
    std::cout << "\n>>> " << FEATURE_NAME << "\n\n";

    // TODO: replace these prompts with the real inputs Soh's logic needs.
    std::cout << "Select a category:\n";
    std::cout << "  1. Category A\n";
    std::cout << "  2. Category B\n";
    std::cout << "  3. Category C\n";
    const int selectedCategory =
        readIntInRange("Enter your choice (1-3): ", CATEGORY_MIN, CATEGORY_MAX);

    const double userValue =
        readDoubleInRange("Enter a value (0-1000): ", VALUE_MIN, VALUE_MAX);

    // Integration point: all validation is done, now hand over to Coding A.
    const std::string result = runCoreLogic(selectedCategory, userValue);

    displayResult(result);
}

// Returns true if the user wants another operation.
bool askToRepeat()
{
    std::cout << "\nWould you like to perform another operation?\n";
    std::cout << "  1. Yes\n";
    std::cout << "  2. No\n";
    const int answer = readIntInRange("Choose an option (1-2): ", 1, 2);
    return answer == 1;
}

// ---------------------------------------------------------------
// Program entry
// ---------------------------------------------------------------

int main()
{
    bool keepRunning = true;

    while (keepRunning)
    {
        showMainMenu();
        const int userChoice =
            readIntInRange("Choose an option (1-3): ", MENU_MAIN_FEATURE, MENU_EXIT);

        switch (userChoice)
        {
            case MENU_MAIN_FEATURE:
                runMainFeature();
                keepRunning = askToRepeat();
                break;

            case MENU_ABOUT:
                showAbout();
                break;

            case MENU_EXIT:
                keepRunning = false;
                break;
        }
    }

    std::cout << "\nThank you for using the program. Goodbye!\n";
    return 0;
}
