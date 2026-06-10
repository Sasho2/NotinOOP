#include "NotinOOP.h"
#include <iostream>

void NotinOOP::handleCheckout() {
    if (!loggedInUser || loggedInUser->isAdmin()) return;

    Buyer* buyer = static_cast<Buyer*>(loggedInUser);
    if (buyer->getCartCount() == 0) {
        std::cout << "[!] Your cart is empty.\n";
        return;
    }

    double total = 0.0;
    for (int i = 0; i < buyer->getCartCount(); i++) {
        total += buyer->getCartItem(i)->getPrice();
    }

    if (buyer->getBalance() < total) {
        std::cout << "[!] Insufficient funds! You need " << total << " EUR but have " << buyer->getBalance() << ".\n";
        return;
    }

    buyer->deductBalance(total);

    for (int i = 0; i < buyer->getCartCount(); i++) {
        buyer->getCartItem(i)->decreaseQuantity();
    }

    buyer->emptyCart();
    std::cout << "[?] Checkout complete! Paid: " << total << " EUR.\n";
}