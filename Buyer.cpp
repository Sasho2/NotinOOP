#include "Buyer.h"
#include <iostream>

void Buyer::resizeCart() {
    cartCapacity = (cartCapacity == 0) ? 2 : cartCapacity * 2;
    Fragrance** temp = new Fragrance * [cartCapacity];
    for (int i = 0; i < cartCount; i++) temp[i] = cart[i];
    delete[] cart;
    cart = temp;
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
    : User(id, uname, pass), balance(0.0),
    cart(nullptr), cartCount(0), cartCapacity(0),
    purchases(nullptr), purchCount(0), purchCapacity(0),
    discounts(nullptr), discCount(0), discCapacity(0) {
}

Buyer::~Buyer() {
    delete[] cart;

    for (int i = 0; i < purchCount; i++) {
        delete purchases[i];
    }
    delete[] purchases;

    for (int i = 0; i < discCount; i++) {
        delete discounts[i];
    }
    delete[] discounts;
}

bool Buyer::isAdmin() const { return false; }

void Buyer::addToBalance(double amount) { if (amount > 0) balance += amount; }
double Buyer::getBalance() const { return balance; }
void Buyer::deductBalance(double amount) { if (amount > 0 && balance >= amount) balance -= amount; }

void Buyer::addToCart(Fragrance* f) {
    if (cartCount == cartCapacity) resizeCart();
    cart[cartCount++] = f;
}

bool Buyer::removeFromCart(const char* fName) {
    String target(fName);
    for (int i = 0; i < cartCount; i++) {
        if (cart[i]->getName() == target) {
            cart[i] = cart[cartCount - 1];
            cart[cartCount - 1] = nullptr;
            cartCount--;
            return true;
        }
    }
    return false;
}

void Buyer::viewCart() const {
    std::cout << "\n--- My Cart ---\n";
    if (cartCount == 0) {
        std::cout << "Empty.\n";
        return;
    }
    double total = 0;
    for (int i = 0; i < cartCount; i++) {
        std::cout << "- " << cart[i]->getName().c_str() << " (" << cart[i]->getPrice() << " EUR)\n";
        total += cart[i]->getPrice();
    }
    std::cout << "Total raw price: " << total << " EUR\n------------------\n";
}

void Buyer::emptyCart() { cartCount = 0; }

void Buyer::addPurchase(Purchase* p) {
    if (purchCount == purchCapacity) resizePurchases();
    purchases[purchCount++] = p;
}

void Buyer::viewPurchases() const {
    std::cout << "\n--- Order History ---\n";
    if (purchCount == 0) {
        std::cout << "No orders yet.\n";
        return;
    }
    for (int i = 0; i < purchCount; i++) {
        purchases[i]->show();
    }
}

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