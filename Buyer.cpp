#include "Buyer.h"

Buyer::Buyer(int id, const char* uname, const char* pass)
    : User(id, uname, pass), balance(0.0) {
}

bool Buyer::isAdmin() const {
    return false;
}

void Buyer::addToBalance(double amount) {
    if (amount > 0) balance += amount;
}

double Buyer::getBalance() const {
    return balance;
}

void Buyer::deductBalance(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
    }
}