#include "NotinOOP.h"
#include <cstdlib>
#include <ctime>
#include <cctype>

static bool equalsIgnoreCase(const char* a, const char* b) {
    if (!a || !b) return false;
    for (; *a && *b; a++, b++) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
    }
    return *a == *b;
}

void NotinOOP::resizeUsers() {
    userCapacity = (userCapacity == 0) ? 2 : userCapacity * 2;
    User** temp = new User * [userCapacity];
    for (int i = 0; i < userCount; i++) temp[i] = users[i];
    delete[] users;
    users = temp;
}

void NotinOOP::resizeCatalog() {
    catalogCapacity = (catalogCapacity == 0) ? 2 : catalogCapacity * 2;
    Fragrance** temp = new Fragrance * [catalogCapacity];
    for (int i = 0; i < catalogCount; i++) temp[i] = catalog[i];
    delete[] catalog;
    catalog = temp;
}

void NotinOOP::resizePurchases() {
    purchCapacity = (purchCapacity == 0) ? 2 : purchCapacity * 2;
    Purchase** temp = new Purchase * [purchCapacity];
    for (int i = 0; i < purchCount; i++) temp[i] = allPurchases[i];
    delete[] allPurchases;
    allPurchases = temp;
}

void NotinOOP::resizeBlacklist() {
    blacklistCapacity = (blacklistCapacity == 0) ? 2 : blacklistCapacity * 2;
    String* temp = new String[blacklistCapacity];
    for (int i = 0; i < blacklistCount; i++) temp[i] = blacklist[i];
    delete[] blacklist;
    blacklist = temp;
}

NotinOOP::NotinOOP() : users(nullptr), userCount(0), userCapacity(0),
catalog(nullptr), catalogCount(0), catalogCapacity(0),
allPurchases(nullptr), purchCount(0), purchCapacity(0),
blacklist(nullptr), blacklistCount(0), blacklistCapacity(0),
loggedInUser(nullptr), nextPurchaseId(1), nextReviewId(1) {
    srand(time(nullptr));
}

NotinOOP::~NotinOOP() {
    for (int i = 0; i < userCount; i++) delete users[i];
    delete[] users;

    for (int i = 0; i < catalogCount; i++) delete catalog[i];
    delete[] catalog;

    for (int i = 0; i < purchCount; i++) delete allPurchases[i];
    delete[] allPurchases;

    delete[] blacklist;
}

Fragrance* NotinOOP::findFragrance(const char* name) const {
    for (int i = 0; i < catalogCount; i++) {
        if (equalsIgnoreCase(catalog[i]->getName().c_str(), name) && !catalog[i]->getIsDeleted()) {
            return catalog[i];
        }
    }
    return nullptr;
}