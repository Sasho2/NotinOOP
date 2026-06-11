#include "NotinOOP.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <iostream>
#include <cstdlib>

void NotinOOP::handleCheckout() {
    if (!loggedInUser || loggedInUser->isAdmin()) return;

    Buyer* buyer = static_cast<Buyer*>(loggedInUser);
    if (buyer->getCartCount() == 0) {
        std::cout << "[!] Your cart is empty. Add something first.\n";
        return;
    }

    double rawTotal = 0.0;
    for (int i = 0; i < buyer->getCartCount(); i++) {
        rawTotal += buyer->getCartItem(i)->getPrice();
    }

    double bestTotal = rawTotal;
    int bestDiscountIndex = -1;

    for (int i = 0; i < buyer->getDiscountCount(); i++) {
        Discount* currentDiscount = buyer->getDiscount(i);
        double currentTotal = 0.0;

        for (int j = 0; j < buyer->getCartCount(); j++) {
            Fragrance* item = buyer->getCartItem(j);
            currentTotal += currentDiscount->apply(item->getPrice(), item->getBrand());
        }

        if (currentTotal < bestTotal) {
            bestTotal = currentTotal;
            bestDiscountIndex = i;
        }
    }

    if (buyer->getBalance() < bestTotal) {
        std::cout << "[!] Insufficient funds! You need " << bestTotal << " EUR but only have " << buyer->getBalance() << " EUR.\n";
        return;
    }

    buyer->deductBalance(bestTotal);
    Purchase* newOrder = new Purchase(nextPurchaseId++, buyer->getId());

    Discount* usedDiscount = (bestDiscountIndex != -1) ? buyer->getDiscount(bestDiscountIndex) : nullptr;

    std::cout << "\n==================================================\n";
    std::cout << "                 RECEIPT\n";
    std::cout << "==================================================\n";

    if (usedDiscount) {
        std::cout << "[✓] Automatically applied voucher:\n  -> ";
        usedDiscount->print();
    }

    for (int i = 0; i < buyer->getCartCount(); i++) {
        Fragrance* item = buyer->getCartItem(i);
        double finalItemPrice = item->getPrice();
        if (usedDiscount) {
            finalItemPrice = usedDiscount->apply(finalItemPrice, item->getBrand());
        }

        newOrder->addFragrance(item, finalItemPrice);
        item->decreaseQuantity();
    }

    if (bestDiscountIndex != -1) {
        buyer->removeDiscount(bestDiscountIndex);
    }

    if (purchCount == purchCapacity) resizePurchases();
    allPurchases[purchCount++] = newOrder;
    buyer->addPurchase(newOrder);
    buyer->emptyCart();

    std::cout << "[✓] Checkout complete! Final Charge: " << bestTotal << " EUR.\n";

    int discType = rand() % 2;
    int newDiscId = rand() % 90000 + 10000;
    double percent = (rand() % 5 + 1) * 10.0;
    Discount* newVoucher = nullptr;

    if (discType == 0) {
        double flatBonus = (rand() % 4) * 5.0;
        newVoucher = new BonusDiscount(newDiscId, percent, flatBonus);
    }
    else {
        Brand randomBrand = static_cast<Brand>(rand() % 4);
        newVoucher = new BrandDiscount(newDiscId, percent, randomBrand);
    }

    buyer->addDiscount(newVoucher);
    std::cout << "\n[!] SURPRISE! You earned a new voucher for your next order:\n  -> ";
    newVoucher->print();
    std::cout << "==================================================\n";
}