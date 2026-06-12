#include "Buyer.h"
#include <iostream>
#include <cctype>

static bool equalsIgnoreCase(const char* a, const char* b) {
    if (!a || !b) return false;
    for (; *a && *b; a++, b++) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
    }
    return *a == *b;
}

void Buyer::resizeCart() {
    cartCapacity = (cartCapacity == 0) ? 2 : cartCapacity * 2;
    Fragrance** temp = new Fragrance * [cartCapacity];
    for (int i = 0; i < cartCount; i++) temp[i] = cart[i];
    delete[] cart;
    cart = temp;
}

void Buyer::resizeWishlist() {
    wishCapacity = (wishCapacity == 0) ? 2 : wishCapacity * 2;
    String* temp = new String[wishCapacity];
    for (int i = 0; i < wishCount; i++) temp[i] = wishlist[i];
    delete[] wishlist;
    wishlist = temp;
}

void Buyer::resizePurchases() {
    purchCapacity = (purchCapacity == 0) ? 2 : purchCapacity * 2;
    Purchase** temp = new Purchase * [purchCapacity];
    for (int i = 0; i < purchCount; i++) temp[i] = purchases[i];
    delete[] purchases;
    purchases = temp;
}

void Buyer::resizeDiscounts() {
    discCapacity = (discCapacity == 0) ? 2 : discCapacity * 2;
    Discount** temp = new Discount * [discCapacity];
    for (int i = 0; i < discCount; i++) temp[i] = discounts[i];
    delete[] discounts;
    discounts = temp;
}

Buyer::Buyer(int id, const char* uname, const char* pass)
    : User(id, uname, pass), cart(nullptr), cartCount(0), cartCapacity(0),
    wishlist(nullptr), wishCount(0), wishCapacity(0),
    purchases(nullptr), purchCount(0), purchCapacity(0),
    discounts(nullptr), discCount(0), discCapacity(0), balance(0.0), deletedReviewsCount(0) {
}

Buyer::~Buyer() {
    delete[] cart;
    delete[] purchases;
    delete[] wishlist;

    for (int i = 0; i < discCount; i++) {
        delete discounts[i];
    }
    delete[] discounts;
}

bool Buyer::isAdmin() const { return false; }

void Buyer::addToBalance(double amount) { if (amount > 0) balance += amount; }
double Buyer::getBalance() const { return balance; }
void Buyer::deductBalance(double amount) { if (amount > 0 && balance >= amount) balance -= amount; }

void Buyer::addDiscount(Discount* d) {
    if (discCount == discCapacity) resizeDiscounts();
    discounts[discCount++] = d;
}

void Buyer::removeDiscount(int index) {
    if (index >= 0 && index < discCount) {
        delete discounts[index];
        discounts[index] = discounts[discCount - 1];
        discounts[discCount - 1] = nullptr;
        discCount--;
    }
}

void Buyer::addToCart(Fragrance* f) {
    if (cartCount == cartCapacity) resizeCart();
    cart[cartCount++] = f;
}

bool Buyer::removeFromCart(const char* fName) {
    for (int i = 0; i < cartCount; i++) {
        if (equalsIgnoreCase(cart[i]->getName().c_str(), fName)) {
            cart[i] = cart[cartCount - 1];
            cart[cartCount - 1] = nullptr;
            cartCount--;
            return true;
        }
    }
    return false;
}

void Buyer::viewCart() const {
    std::cout << "\n--- Cart for " << username.c_str() << " ---\n";
    if (cartCount == 0) {
        std::cout << "Empty.\n";
        return;
    }

    double total = 0;
    for (int i = 0; i < cartCount; i++) {
        std::cout << "- " << cart[i]->getName().c_str() << " (" << cart[i]->getDiscountedPrice() << " EUR)\n";
        total += cart[i]->getDiscountedPrice();
    }
    std::cout << "Total to pay: " << total << " EUR\n------------------\n";
}

void Buyer::emptyCart() { cartCount = 0; }

void Buyer::addToWishlist(const char* fName) {
    if (isInWishlist(fName)) {
        std::cout << "[Info] Already in wishlist.\n";
        return;
    }
    if (wishCount == wishCapacity) resizeWishlist();
    wishlist[wishCount++] = String(fName);
    std::cout << "[Success] Added to wishlist.\n";
}

bool Buyer::removeFromWishlist(const char* fName) {
    for (int i = 0; i < wishCount; i++) {
        if (equalsIgnoreCase(wishlist[i].c_str(), fName)) {
            wishlist[i] = wishlist[wishCount - 1];
            wishCount--;
            return true;
        }
    }
    return false;
}

bool Buyer::isInWishlist(const char* fName) const {
    for (int i = 0; i < wishCount; i++) {
        if (equalsIgnoreCase(wishlist[i].c_str(), fName)) return true;
    }
    return false;
}

void Buyer::addPurchase(Purchase* p) {
    if (purchCount == purchCapacity) resizePurchases();
    purchases[purchCount++] = p;
}

void Buyer::viewBought() const {
    std::cout << "\n--- Successful Purchases ---\n";
    for (int i = 0; i < purchCount; i++) {
        if (purchases[i]->getStatus() == OrderStatus::DELIVERED) {
            purchases[i]->show();
        }
    }
}

void Buyer::viewPurchases() const {
    std::cout << "\n--- All Purchases ---\n";
    for (int i = 0; i < purchCount; i++) {
        purchases[i]->show();
    }
}

bool Buyer::canReview(Fragrance* f) const {
    if (!f) return false;
    int boughtOrders = 0;

    for (int i = 0; i < purchCount; i++) {
        for (int j = 0; j < purchases[i]->getFragCount(); j++) {
            if (purchases[i]->getFragrance(j) == f) {
                boughtOrders++;
                break;
            }
        }
    }

    int writtenReviews = f->getReviewCountByUser(username.c_str());
    return boughtOrders > writtenReviews;
}

bool Buyer::hasBought(const char* fName) const {
    for (int i = 0; i < purchCount; i++) {
        for (int j = 0; j < purchases[i]->getFragCount(); j++) {
            if (equalsIgnoreCase(purchases[i]->getFragrance(j)->getName().c_str(), fName)) {
                return true;
            }
        }
    }
    return false;
}

void Buyer::adminInspect() const {
    std::cout << "\n=== DOSSIER: " << username.c_str() << " (ID: " << userId << ") ===\n";
    std::cout << "Wallet Balance: " << balance << " EUR\n";
    std::cout << "Strikes (Deleted Reviews): " << deletedReviewsCount << " / 7\n";
    std::cout << "\n[ CURRENT CART ]";
    viewCart();
    std::cout << "[ ORDER HISTORY ]";
    viewPurchases();
    std::cout << "\n[ WISHLIST ]\n";
    if (wishCount == 0) std::cout << "Empty.\n";
    for (int i = 0; i < wishCount; i++) std::cout << "- " << wishlist[i].c_str() << "\n";
    std::cout << "\n[ ACTIVE VOUCHERS ]\n";
    if (discCount == 0) std::cout << "None.\n";
    for (int i = 0; i < discCount; i++) discounts[i]->print();
    std::cout << "========================================\n";
}