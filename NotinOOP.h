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

    String* blacklist;
    int blacklistCount;
    int blacklistCapacity;

    User* loggedInUser;

    int nextPurchaseId;
    int nextReviewId;

    void resizeUsers();
    void resizeCatalog();
    void resizePurchases();
    void resizeBlacklist();

    void handleCheckout();
    void handleRecommend();

public:
    NotinOOP();
    ~NotinOOP();

    void run();

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    Fragrance* findFragrance(const char* name) const;
};