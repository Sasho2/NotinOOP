#pragma once
#include "User.h"
#include "Buyer.h"
#include "Admin.h"

class NotinOOP {
private:
    User** users;
    int userCount;
    int userCapacity;
    User* loggedInUser;

    void resizeUsers();

public:
    NotinOOP();
    ~NotinOOP();

    void run();
};