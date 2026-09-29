#ifndef LOGIC_H
#define LOGIC_H
#include <string>
#include <vector>
// Integer sen avoids rounding. This classroom cap is not a TNG rule.
constexpr int MAX_BALANCE_SEN = 100000;
struct Transaction {
    int id;
    std::string type, merchant;
    int amountSen, balanceAfterSen;
};
struct Result { bool success; std::string message; };
bool parseAmount(const std::string& text, int& amountSen);
std::string formatMoney(int amountSen);
std::string merchantName(int choice);
class Wallet {
public:
    int balance() const { return balanceSen_; }
    const std::vector<Transaction>& history() const { return transactions_; }
    Result topUp(int amountSen);
    Result pay(int merchant, int amountSen);
private:
    int balanceSen_ = 0;
    std::vector<Transaction> transactions_;
    Result record(const std::string& type, const std::string& merchant,
                  int amountSen, int newBalanceSen);
};
#endif
