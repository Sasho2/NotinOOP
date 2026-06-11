#pragma once
#include "User.h"
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"
#include "Purchase.h"

class NotinOOP {
private:
    User** users;
    int userCount;
    int userCapacity;

    Fragrance** catalog;
    int catalogCount;
    int catalogCapacity;

    Purchase** allPurchases;
    int purchCount;
    int purchCapacity;

    User* loggedInUser;

    int nextPurchaseId;
    int nextReviewId;

    void resizeUsers();
    void resizeCatalog();
    void resizePurchases();

public:
    NotinOOP();
    ~NotinOOP();

    void run();
    Fragrance* findFragrance(const char* name) const;
    void handleCheckout();

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
};