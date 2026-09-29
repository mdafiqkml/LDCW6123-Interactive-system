#include "logic.h"
#include <iomanip>
#include <sstream>

bool parseAmount(const std::string& text, int& amountSen)
{
    // Parse decimal text directly so floating-point rounding cannot lose a sen.
    if (text.empty() || text.size() > 7) return false;
    const auto dot = text.find('.');
    const auto wholeLength = dot == std::string::npos ? text.size() : dot;
    if (wholeLength == 0 || wholeLength > 4) return false;
    const auto fractionLength = dot == std::string::npos ? 0 : text.size() - dot - 1;
    if (dot != std::string::npos && (fractionLength == 0 || fractionLength > 2)) return false;
    int whole = 0, fraction = 0;
    for (std::size_t i = 0; i < wholeLength; ++i) {
        if (text[i] < '0' || text[i] > '9') return false;
        whole = whole * 10 + (text[i] - '0');
    }
    for (std::size_t i = 0; i < fractionLength; ++i) {
        const char digit = text[dot + 1 + i];
        if (digit < '0' || digit > '9') return false;
        fraction = fraction * 10 + (digit - '0');
    }
    if (fractionLength == 1) fraction *= 10;
    const int parsed = whole * 100 + fraction;
    if (parsed < 1 || parsed > MAX_BALANCE_SEN) return false;
    amountSen = parsed;
    return true;
}

std::string formatMoney(int amountSen)
{
    std::ostringstream output;
    output << "RM" << amountSen / 100 << '.' << std::setw(2)
           << std::setfill('0') << amountSen % 100;
    return output.str();
}

std::string merchantName(int choice)
{
    switch (choice) {
        case 1: return "Campus Cafe";
        case 2: return "Campus Bookshop";
        case 3: return "Campus Mini Mart";
        default: return "";
    }
}

Result Wallet::record(const std::string& type, const std::string& merchant,
                      int amountSen, int newBalanceSen)
{
    const int id = static_cast<int>(transactions_.size()) + 1;
    transactions_.push_back({id, type, merchant, amountSen, newBalanceSen});
    balanceSen_ = newBalanceSen;
    return {true, "Transaction #" + std::to_string(id) + " | " + type + " | " + merchant
        + " | " + formatMoney(amountSen) + "\nBalance: " + formatMoney(balanceSen_)};
}

Result Wallet::topUp(int amountSen)
{
    if (amountSen <= 0 || amountSen > MAX_BALANCE_SEN)
        return {false, "Amount must be RM0.01 to RM1000.00."};
    if (amountSen > MAX_BALANCE_SEN - balanceSen_)
        return {false, "Top-up rejected: simulation balance limit is RM1000.00."};
    return record("TOP UP", "Demo funds", amountSen, balanceSen_ + amountSen);
}

Result Wallet::pay(int merchant, int amountSen)
{
    const auto name = merchantName(merchant);
    if (name.empty()) return {false, "Unknown merchant."};
    if (amountSen <= 0 || amountSen > MAX_BALANCE_SEN)
        return {false, "Amount must be RM0.01 to RM1000.00."};
    if (amountSen > balanceSen_)
        return {false, "Payment rejected: insufficient funds. Balance: " + formatMoney(balanceSen_)};
    return record("PAYMENT", name, amountSen, balanceSen_ - amountSen);
}
