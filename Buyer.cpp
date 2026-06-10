#include "Buyer.h"
#include <iostream>

void Buyer::resizeCart() {
    cartCapacity = (cartCapacity == 0) ? 2 : cartCapacity * 2;
    Fragrance** temp = new Fragrance * [cartCapacity];
    for (int i = 0; i < cartCount; i++) temp[i] = cart[i];
    delete[] cart;
    cart = temp;
}

Buyer::Buyer(int id, const char* uname, const char* pass)
    : User(id, uname, pass), balance(0.0), cart(nullptr), cartCount(0), cartCapacity(0) {
}

Buyer::~Buyer() {
    delete[] cart;
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
    if (amount > 0 && balance >= amount)
        balance -= amount;
}

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
    std::cout << "Total: " << total << " EUR\n----------------\n";
}

void Buyer::emptyCart() {
    cartCount = 0;
}