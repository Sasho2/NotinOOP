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
        std::cout << "[!] Insufficient funds.\n";
        return;
    }

    buyer->deductBalance(total);
    Purchase* newOrder = new Purchase(nextPurchaseId++, buyer->getId());

    for (int i = 0; i < buyer->getCartCount(); i++) {
        Fragrance* item = buyer->getCartItem(i);
        newOrder->addFragrance(item, item->getPrice());
        item->decreaseQuantity();
    }

    if (purchCount == purchCapacity) resizePurchases();
    allPurchases[purchCount++] = newOrder;
    buyer->addPurchase(newOrder);
    buyer->emptyCart();

    std::cout << "[✓] Checkout complete! Order #" << newOrder->getId() << " is pending.\n";
}