#include "NotinOOP.h"

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

NotinOOP::NotinOOP() : users(nullptr), userCount(0), userCapacity(0),catalog(nullptr), 
catalogCount(0), catalogCapacity(0),loggedInUser(nullptr), allPurchases(nullptr), purchCount(0), purchCapacity(0), nextPurchaseId(0) {}

NotinOOP::~NotinOOP() {
    for (int i = 0; i < userCount; i++) delete users[i];
    delete[] users;

    for (int i = 0; i < catalogCount; i++) delete catalog[i];
    delete[] catalog;

	for (int i = 0; i < purchCount; i++) delete allPurchases[i];
	delete[] allPurchases;
}

Fragrance* NotinOOP::findFragrance(const char* name) const {
    String target(name);
    for (int i = 0; i < catalogCount; i++) {
        if (catalog[i]->getName() == target) {
            return catalog[i];
        }
    }
    return nullptr;
}