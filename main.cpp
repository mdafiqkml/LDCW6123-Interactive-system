// Interaction layer continued from the supplied main.cpp.
// Original trim, line input and integer-validation approach retained.
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include "logic.h"

std::string trim(const std::string& text)
{
    const std::string whitespace = " \t\r\n";
    const auto start = text.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    return text.substr(start, text.find_last_not_of(whitespace) - start + 1);
}
std::string readLineOrExit()
{
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout << "\nNo more input. Session ended; demo data is not saved.\n";
        std::exit(0);
    }
    return trim(line);
}
int readIntInRange(const std::string& prompt, int minimum, int maximum)
{
    while (true) {
        std::cout << prompt;
        const auto text = readLineOrExit();
        if (text.empty() || text.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Invalid choice. Enter a whole number.\n";
            continue;
        }
        try {
            const int value = std::stoi(text);
            if (value >= minimum && value <= maximum) return value;
        } catch (const std::exception&) { }
        std::cout << "Choose a number from " << minimum << " to " << maximum << ".\n";
    }
}
int readAmount()
{
    while (true) {
        std::cout << "Amount in RM (0.01-1000.00, up to 2 decimal places): ";
        int amount = 0;
        if (parseAmount(readLineOrExit(), amount)) return amount;
        std::cout << "Invalid amount. Example: 12.50. No signs or extra text.\n";
    }
}
bool confirm(const std::string& action, int amount)
{
    std::cout << action << " " << formatMoney(amount) << "?\n";
    return readIntInRange("1. Confirm  2. Cancel: ", 1, 2) == 1;
}
void showHistory(const Wallet& wallet)
{
    std::cout << "\nSESSION TRANSACTION HISTORY\n";
    if (wallet.history().empty()) std::cout << "No successful transactions yet.\n";
    for (const auto& entry : wallet.history()) {
        std::cout << '#' << entry.id << " | " << entry.type << " | " << entry.merchant
                  << " | " << formatMoney(entry.amountSen)
                  << " | Balance " << formatMoney(entry.balanceAfterSen) << '\n';
    }
}
void showAbout()
{
    std::cout << "\nInspired by Touch 'n Go eWallet cashless merchant payments.\n"
              << "Offline educational simulation; no real money or official affiliation.\n"
              << "Merchants are fictional. No QR scanner, bank connection or login.\n"
              << "Balance limit RM1000.00 is a classroom rule, not TNG policy.\n"
              << "All session data resets when you exit.\n"
              << "Winston connection: cashless convenience supports adoption;\n"
              << "trust, access and institutional controls shape actual use.\n";
}
int main()
{
    Wallet wallet;
    std::cout << "TNG-INSPIRED CAMPUS WALLET SIMULATOR\n"
              << "Demo only. Starting balance RM0.00. No real payments.\n";
    bool running = true;
    while (running) {
        std::cout << "\n==================================================\n"
                  << "Balance: " << formatMoney(wallet.balance()) << '\n'
                  << "1. Top up demo funds\n2. Pay a demo merchant\n"
                  << "3. View balance\n4. View transaction history\n"
                  << "5. About this simulation\n6. Exit\n";
        switch (readIntInRange("Choose (1-6): ", 1, 6)) {
            case 1: {
                const int amount = readAmount();
                if (confirm("Top up", amount)) std::cout << wallet.topUp(amount).message << '\n';
                else std::cout << "Cancelled. Balance unchanged.\n";
                break;
            }
            case 2: {
                std::cout << "1. Campus Cafe\n2. Campus Bookshop\n3. Campus Mini Mart\n";
                const int merchant = readIntInRange("Choose merchant (1-3): ", 1, 3);
                const int amount = readAmount();
                if (confirm("Pay " + merchantName(merchant), amount))
                    std::cout << wallet.pay(merchant, amount).message << '\n';
                else std::cout << "Cancelled. Balance unchanged.\n";
                break;
            }
            case 3: std::cout << "Available balance: " << formatMoney(wallet.balance()) << '\n'; break;
            case 4: showHistory(wallet); break;
            case 5: showAbout(); break;
            case 6: running = false; break;
        }
    }
    std::cout << "Goodbye. Session ended; demo data is not saved.\n";
    return 0;
}
