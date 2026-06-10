#pragma once
#include "User.h"
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"

class NotinOOP {
private:
    User** users;
    int userCount;
    int userCapacity;

    Fragrance** catalog;
    int catalogCount;
    int catalogCapacity;

    User* loggedInUser;

    void resizeUsers();
    void resizeCatalog();

public:
    NotinOOP();
    ~NotinOOP();

    void run();
    void handleCheckout();

    Fragrance* findFragrance(const char* name) const;
};