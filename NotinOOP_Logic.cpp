#include "NotinOOP.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

void NotinOOP::handleCheckout() {
    if (!loggedInUser || loggedInUser->isAdmin()) return;

    Buyer* buyer = static_cast<Buyer*>(loggedInUser);
    if (buyer->getCartCount() == 0) {
        std::cout << "[!] Your cart is empty. Add something first.\n";
        return;
    }

    double storeTotal = 0.0;
    for (int i = 0; i < buyer->getCartCount(); i++) {
        storeTotal += buyer->getCartItem(i)->getDiscountedPrice();
    }

    double bestTotal = storeTotal;
    int bestDiscountIndex = -1;

    for (int i = 0; i < buyer->getDiscountCount(); i++) {
        Discount* currentDiscount = buyer->getDiscount(i);
        double currentTotal = 0.0;

        for (int j = 0; j < buyer->getCartCount(); j++) {
            Fragrance* item = buyer->getCartItem(j);
            currentTotal += currentDiscount->apply(item->getDiscountedPrice(), item->getBrand());
        }

        if (currentTotal < bestTotal) {
            bestTotal = currentTotal;
            bestDiscountIndex = i;
        }
    }

    if (buyer->getBalance() < bestTotal) {
        std::cout << "[!] You are broke! You need " << bestTotal << " EUR but only have " << buyer->getBalance() << " EUR.\n";
        return;
    }

    buyer->deductBalance(bestTotal);
    Purchase* newOrder = new Purchase(nextPurchaseId++, buyer->getId());

    Discount* usedDiscount = (bestDiscountIndex != -1) ? buyer->getDiscount(bestDiscountIndex) : nullptr;

    std::cout << "\n==================================================\n";
    std::cout << "                 RECEIPT\n";
    std::cout << "==================================================\n";
    std::cout << "Items Total (incl. Store Sales): " << storeTotal << " EUR\n";

    if (usedDiscount) {
        std::cout << "[✓] Automatically applied your best voucher:\n  -> ";
        usedDiscount->print();
        std::cout << "Voucher Savings: " << (storeTotal - bestTotal) << " EUR\n";
    }
    else {
        std::cout << "No personal vouchers applied.\n";
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << "FINAL CHARGE: " << bestTotal << " EUR\n";
    std::cout << "==================================================\n";

    Fragrance* uniqueItems[100];
    int uniqueCount = 0;

    for (int i = 0; i < buyer->getCartCount(); i++) {
        Fragrance* item = buyer->getCartItem(i);
        double finalItemPrice = item->getDiscountedPrice();
        if (usedDiscount) {
            finalItemPrice = usedDiscount->apply(finalItemPrice, item->getBrand());
        }

        newOrder->addFragrance(item, finalItemPrice);
        item->decreaseQuantity();

        bool found = false;
        for (int u = 0; u < uniqueCount; u++) {
            if (uniqueItems[u] == item) { found = true; break; }
        }
        if (!found && uniqueCount < 100) {
            uniqueItems[uniqueCount++] = item;
        }
    }

    if (bestDiscountIndex != -1) buyer->removeDiscount(bestDiscountIndex);

    if (purchCount == purchCapacity) resizePurchases();
    allPurchases[purchCount++] = newOrder;
    buyer->addPurchase(newOrder);
    buyer->emptyCart();

    std::cout << "    Remaining wallet balance: " << buyer->getBalance() << " EUR.\n";

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

    std::cout << "\n--- Leave a Review? ---\n";
    for (int i = 0; i < uniqueCount; i++) {
        if (buyer->canReview(uniqueItems[i])) {
            std::cout << "Would you like to review '" << uniqueItems[i]->getName().c_str() << "' right now? (y/n): ";
            char ans;
            std::cin >> ans;
            std::cin.ignore(10000, '\n');

            if (ans == 'y' || ans == 'Y') {
                std::cout << "Rating (1-5): ";
                int rating;
                std::cin >> rating;
                if (std::cin.fail() || rating < 1 || rating > 5) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid rating. Skipped.\n";
                    continue;
                }
                std::cin.ignore(10000, '\n');

                std::cout << "Comment: ";
                char comm[1024];
                std::cin.getline(comm, 1024);

                Review* r = new Review(nextReviewId++, buyer->getUsername().c_str(), comm, rating);
                uniqueItems[i]->addReview(r);
                std::cout << "[✓] Review published. Thank you!\n";
            }
            else {
                std::cout << " -> Skipped. You can do it later via menu.\n";
            }
        }
    }
}

void NotinOOP::handleRecommend() {
    if (!loggedInUser || loggedInUser->isAdmin()) return;
    Buyer* buyer = static_cast<Buyer*>(loggedInUser);

    int familyCounts[10] = { 0 };
    int brandCounts[10] = { 0 };
    int itemsAnalyzed = 0;

    for (int i = 0; i < buyer->getWishlistCount(); i++) {
        Fragrance* f = findFragrance(buyer->getWishlistItem(i).c_str());
        if (f) {
            familyCounts[static_cast<int>(f->getFamily())]++;
            brandCounts[static_cast<int>(f->getBrand())]++;
            itemsAnalyzed++;
        }
    }

    for (int i = 0; i < catalogCount; i++) {
        if (!catalog[i]->getIsDeleted() && buyer->hasBought(catalog[i]->getName().c_str())) {
            familyCounts[static_cast<int>(catalog[i]->getFamily())]++;
            brandCounts[static_cast<int>(catalog[i]->getBrand())]++;
            itemsAnalyzed++;
        }
    }

    std::cout << "\n======================================================================\n";
    std::cout << "                      AI SMART RECOMMENDATIONS                        \n";
    std::cout << "======================================================================\n";

    int recommendedCount = 0;
    Fragrance* recs[3] = { nullptr, nullptr, nullptr };

    if (itemsAnalyzed > 0) {
        int favFamilyInt = 0, favBrandInt = 0;
        int maxFam = -1, maxBrand = -1;
        for (int i = 0; i < 10; i++) {
            if (familyCounts[i] > maxFam) { maxFam = familyCounts[i]; favFamilyInt = i; }
            if (brandCounts[i] > maxBrand) { maxBrand = brandCounts[i]; favBrandInt = i; }
        }

        FragranceFamily favFamily = static_cast<FragranceFamily>(favFamilyInt);
        Brand favBrand = static_cast<Brand>(favBrandInt);

        std::cout << " [ Profile ] Favorite Brand: " << brandToString(favBrand)
            << " | Favorite Notes: " << familyToString(favFamily) << "\n\n";

        for (int i = 0; i < catalogCount && recommendedCount < 3; i++) {
            Fragrance* c = catalog[i];
            if (!c->getIsDeleted() && !buyer->hasBought(c->getName().c_str()) && !buyer->isInWishlist(c->getName().c_str())) {
                if (c->getBrand() == favBrand && c->getFamily() == favFamily) {
                    std::cout << "  -> [PERFECT MATCH] " << c->getName().c_str() << " | " << c->getDiscountedPrice() << " EUR\n";
                    recs[recommendedCount++] = c;
                }
            }
        }

        for (int i = 0; i < catalogCount && recommendedCount < 3; i++) {
            Fragrance* c = catalog[i];
            bool alreadyIn = false;
            for (int r = 0; r < recommendedCount; r++) if (recs[r] == c) alreadyIn = true;

            if (!alreadyIn && !c->getIsDeleted() && !buyer->hasBought(c->getName().c_str()) && !buyer->isInWishlist(c->getName().c_str())) {
                if (c->getBrand() == favBrand || c->getFamily() == favFamily) {
                    std::cout << "  -> [GOOD MATCH] " << c->getName().c_str() << " | " << c->getDiscountedPrice() << " EUR\n";
                    recs[recommendedCount++] = c;
                }
            }
        }
    }
    else {
        std::cout << " [!] No purchase history yet. Let's start with the bestsellers:\n\n";
    }

    if (recommendedCount < 3) {
        Fragrance** sorted = new Fragrance * [catalogCount];
        int validCount = 0;

        for (int i = 0; i < catalogCount; i++) {
            Fragrance* c = catalog[i];
            bool alreadyIn = false;
            for (int r = 0; r < recommendedCount; r++) if (recs[r] == c) alreadyIn = true;

            if (!alreadyIn && !c->getIsDeleted() && !buyer->hasBought(c->getName().c_str()) && !buyer->isInWishlist(c->getName().c_str())) {
                sorted[validCount++] = c;
            }
        }

        for (int i = 0; i < validCount - 1; i++) {
            for (int j = i + 1; j < validCount; j++) {
                if (sorted[j]->getRating() > sorted[i]->getRating()) {
                    Fragrance* temp = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = temp;
                }
            }
        }

        for (int i = 0; i < validCount && recommendedCount < 3; i++) {
            std::cout << "  -> [DISCOVERY - " << std::setprecision(2) << sorted[i]->getRating() << std::setprecision(6) << "/5] "
                << sorted[i]->getName().c_str() << " | " << sorted[i]->getDiscountedPrice() << " EUR\n";
            recs[recommendedCount++] = sorted[i];
        }

        delete[] sorted;
    }

    if (recommendedCount == 0) {
        std::cout << "  -> You literally own or wishlisted everything. You broke the store.\n";
    }

    std::cout << "======================================================================\n";
}