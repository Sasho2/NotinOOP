#pragma once
#include "User.h"

class Buyer : public User {
private:
    double balance;

public:
    Buyer(int id, const char* uname, const char* pass);
    ~Buyer() override = default;

    bool isAdmin() const override;

    void addToBalance(double amount);
    double getBalance() const;
    void deductBalance(double amount);
};