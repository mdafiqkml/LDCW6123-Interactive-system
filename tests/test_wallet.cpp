#include "../logic.h"
#include <iostream>
#include <stdexcept>
#include <limits>
int checks = 0;
void check(bool condition, const char* name) {
    ++checks;
    if (!condition) throw std::runtime_error(name);
}
int main() {
    try {
        int amount = 123;
        check(parseAmount("0.01", amount) && amount == 1, "one sen");
        check(parseAmount("12.5", amount) && amount == 1250, "one decimal");
        check(parseAmount("1000.00", amount) && amount == 100000, "maximum");
        check(parseAmount("10", amount) && amount == 1000, "integer amount");
        for (const auto* bad : {"", "0", "0.00", "-1", "+1", "nan", "inf", "1e2", ".5", "1.",
                               "1.001", "12abc", "1.2.3", "1000.01", "999999999999999999", "1 2", " 2", "2 "}) {
            amount = 987;
            check(!parseAmount(bad, amount) && amount == 987, "invalid amount leaves output unchanged");
        }
        check(formatMoney(1) == "RM0.01", "format cent");
        check(formatMoney(1250) == "RM12.50", "format money");
        Wallet wallet;
        check(wallet.balance() == 0 && wallet.history().empty(), "initial state");
        check(!wallet.pay(1, 1).success && wallet.history().empty(), "empty wallet payment");
        check(wallet.topUp(10000).success, "topup 100");
        check(wallet.pay(1, 1250).success && wallet.balance() == 8750, "payment 12.50");
        check(!wallet.pay(2, 9000).success && wallet.balance() == 8750, "insufficient funds unchanged");
        check(wallet.history().size() == 2, "rejection does not record");
        check(wallet.history()[1].id == 2 && wallet.history()[1].balanceAfterSen == 8750, "receipt sequence");
        for (int bad : {0, -1, 100001, std::numeric_limits<int>::max()}) {
            check(!wallet.topUp(bad).success, "invalid core topup");
            check(!wallet.pay(1, bad).success, "invalid core payment");
        }
        check(!wallet.pay(0, 1).success && !wallet.pay(4, 1).success, "invalid merchant");
        check(wallet.balance() == 8750 && wallet.history().size() == 2, "invalid core calls unchanged");
        check(wallet.topUp(91250).success && wallet.balance() == 100000, "fill to cap");
        check(!wallet.topUp(1).success && wallet.balance() == 100000, "over cap unchanged");
        check(wallet.pay(3, 100000).success && wallet.balance() == 0, "exact balance payment");
        check(wallet.topUp(10).success && wallet.topUp(20).success && wallet.balance() == 30, "exact 0.10 plus 0.20");
        check(wallet.pay(2, 30).success && wallet.balance() == 0, "exact cents spend");
        std::cout << "PASS: " << checks << " core checks\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n'; return 1;
    }
}
