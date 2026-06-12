#include "NotinOOP.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

static bool equalsIgnoreCase(const char* a, const char* b) {
    if (!a || !b) return false;
    for (; *a && *b; a++, b++) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
    }
    return *a == *b;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForKey() {
    std::cout << "\n[ Press Enter to return to menu ]";
    std::cin.get();
}

Brand parseBrand(int b) {
    switch (b) {
    case 1: return Brand::CHANEL;
    case 2: return Brand::DIOR;
    case 3: return Brand::TOM_FORD;
    case 4: return Brand::GUCCI;
    default: return Brand::UNKNOWN;
    }
}

FragranceFamily parseFamily(int f) {
    switch (f) {
    case 1: return FragranceFamily::CITRUS;
    case 2: return FragranceFamily::FLORAL;
    case 3: return FragranceFamily::WOODY;
    case 4: return FragranceFamily::ORIENTAL;
    default: return FragranceFamily::FRESH;
    }
}

void NotinOOP::run() {
    if (userCount == 0) {
        resizeUsers();
        users[userCount++] = new Admin(1, "admin", "admin123");
    }

    char choice[10];

    while (true) {
        clearScreen();

        std::cout << "======================================================================\n";
        std::cout << "                        NOTINOOP PREMIUM STORE                        \n";
        std::cout << "======================================================================\n";

        if (!loggedInUser) {
            std::cout << " [ Guest Area ]\n";
            std::cout << "  1. Read Reviews\n";
            std::cout << "  2. Login\n";
            std::cout << "  3. Register\n";
            std::cout << "  0. Exit\n";
        }
        else if (loggedInUser->isAdmin()) {
            std::cout << " [ Admin Panel: " << loggedInUser->getUsername().c_str() << " ]\n";
            std::cout << "  1. Add New Fragrance\n";
            std::cout << "  2. Add Quantity to Stock\n";
            std::cout << "  3. Manage Store Sales & Discounts\n";
            std::cout << "  4. Deliver Pending Orders\n";
            std::cout << "  5. Block a User\n";
            std::cout << "  6. View All Buyers\n";
            std::cout << "  7. Inspect User Dossier\n";
            std::cout << "  8. Delete Review\n";
            std::cout << "  9. Delete Fragrance from Store\n";
            std::cout << "  10. Logout\n";
            std::cout << "  0. Exit\n";
        }
        else {
            std::cout << " [ Buyer: " << loggedInUser->getUsername().c_str()
                << " | Wallet: " << static_cast<Buyer*>(loggedInUser)->getBalance() << " EUR ]\n";
            std::cout << " --- SHOPPING ---\n";
            std::cout << "  1. Read Reviews\n";
            std::cout << "  2. Add to Cart\n";
            std::cout << "  3. Remove from Cart\n";
            std::cout << "  4. View Cart & Checkout\n";
            std::cout << "  5. Manage Wishlist\n";
            std::cout << " --- ACCOUNT ---\n";
            std::cout << "  6. Add Funds\n";
            std::cout << "  7. Order History (Cancel Orders)\n";
            std::cout << "  8. My Vouchers\n";
            std::cout << "  9. Write Review\n";
            std::cout << "  10. AI Recommendations\n";
            std::cout << "  11. Logout\n";
            std::cout << "  0. Exit\n";
        }

        std::cout << "======================================================================\n";
        std::cout << "                            STORE CATALOG                             \n";
        std::cout << "======================================================================\n";

        int visibleCount = 0;
        for (int i = 0; i < catalogCount; i++) {
            if (!catalog[i]->getIsDeleted()) {
                std::cout << " -> " << catalog[i]->getName().c_str();
                if (catalog[i]->getSaleDiscount() > 0) {
                    std::cout << " [ -" << catalog[i]->getSaleDiscount() << "% SALE ]";
                }
                std::cout << " | Brand: " << brandToString(catalog[i]->getBrand())
                    << " | Note: " << familyToString(catalog[i]->getFamily())
                    << " | Price: ";

                if (catalog[i]->getSaleDiscount() > 0) {
                    std::cout << catalog[i]->getDiscountedPrice() << " EUR (was " << catalog[i]->getPrice() << ")";
                }
                else {
                    std::cout << catalog[i]->getPrice() << " EUR";
                }

                std::cout << " | Rating: " << catalog[i]->getRating() << "/5"
                    << " | In Stock: " << catalog[i]->getQuantity() << "\n";
                visibleCount++;
            }
        }
        if (visibleCount == 0) {
            std::cout << " [!] The shelves are empty. Check back later.\n";
        }
        std::cout << "======================================================================\n\n";

        std::cout << "> Select an option: ";
        std::cin >> choice;
        std::cin.ignore(10000, '\n');
        std::cout << "\n";

        if (strcmp(choice, "0") == 0) {
            std::cout << "[System] Saving data to database.txt...\n";
            saveToFile("database.txt");
            std::cout << "[System] Safe shutdown complete. Goodbye!\n";
            break;
        }

        if (strcmp(choice, "1") == 0 && (!loggedInUser || !loggedInUser->isAdmin())) {
            std::cout << "Enter fragrance name to read reviews: ";
            char name[128];
            std::cin >> name;
            std::cin.ignore(10000, '\n');

            Fragrance* f = findFragrance(name);
            if (f) f->printReviews();
            else std::cout << "[!] Fragrance not found.\n";
        }

        else if (!loggedInUser) {
            if (strcmp(choice, "2") == 0) {
                char user[64], pass[64];
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                std::cin.ignore(10000, '\n');

                bool found = false;
                for (int i = 0; i < userCount; i++) {
                    if (equalsIgnoreCase(users[i]->getUsername().c_str(), user) && users[i]->checkPassword(pass)) {
                        loggedInUser = users[i];
                        found = true;
                        std::cout << "[✓] Login successful!\n";
                        break;
                    }
                }
                if (!found) std::cout << "[!] Wrong credentials.\n";
            }
            else if (strcmp(choice, "3") == 0) {
                char user[64], pass[64];
                std::cout << "Choose Username: "; std::cin >> user;
                std::cout << "Choose Password: "; std::cin >> pass;
                std::cin.ignore(10000, '\n');

                bool exists = false;
                for (int i = 0; i < userCount; i++) {
                    if (equalsIgnoreCase(users[i]->getUsername().c_str(), user)) { exists = true; break; }
                }

                bool blacklisted = false;
                for (int i = 0; i < blacklistCount; i++) {
                    if (equalsIgnoreCase(blacklist[i].c_str(), user)) { blacklisted = true; break; }
                }

                if (blacklisted) {
                    std::cout << "[!] Nice try. This username is permanently banned.\n";
                }
                else if (exists) {
                    std::cout << "[!] Username taken.\n";
                }
                else {
                    if (userCount == userCapacity) resizeUsers();
                    users[userCount++] = new Buyer(userCount + 1, user, pass);
                    std::cout << "[✓] Registration complete! You can now login.\n";
                }
            }
            else if (strcmp(choice, "1") != 0) {
                std::cout << "[!] Invalid option.\n";
            }
        }

        else if (loggedInUser->isAdmin()) {
            if (strcmp(choice, "1") == 0) {
                char name[64];
                int bInt, fInt, qty;
                double price;

                std::cout << "Fragrance Name (no spaces): "; std::cin >> name;
                std::cout << "Brand (1-CHANEL, 2-DIOR, 3-TOM_FORD, 4-GUCCI): "; std::cin >> bInt;
                std::cout << "Price (EUR): "; std::cin >> price;
                std::cout << "Family (1-CITRUS, 2-FLORAL, 3-WOODY, 4-ORIENTAL, 5-FRESH): "; std::cin >> fInt;
                std::cout << "Quantity: "; std::cin >> qty;

                if (std::cin.fail() || bInt < 1 || bInt > 4 || fInt < 1 || fInt > 5 || price < 0 || qty < 0) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid input bounds. Setup cancelled.\n";
                }
                else {
                    std::cin.ignore(10000, '\n');
                    if (catalogCount == catalogCapacity) resizeCatalog();
                    catalog[catalogCount++] = new Fragrance(catalogCount + 1, name, parseBrand(bInt), price, parseFamily(fInt), qty);
                    std::cout << "[✓] Successfully added " << name << " to the catalog!\n";
                }
            }
            else if (strcmp(choice, "2") == 0) {
                char name[128];
                int qty;
                std::cout << "Fragrance Name: "; std::cin >> name;
                std::cout << "Quantity to add: "; std::cin >> qty;

                if (std::cin.fail()) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid input.\n";
                }
                else {
                    std::cin.ignore(10000, '\n');
                    Fragrance* f = findFragrance(name);
                    if (f) {
                        if (qty > 0) {
                            f->addQuantity(qty);
                            std::cout << "[✓] Added " << qty << " items to " << f->getName().c_str() << ". New stock: " << f->getQuantity() << "\n";
                        }
                        else std::cout << "[!] Quantity must be positive.\n";
                    }
                    else std::cout << "[!] Fragrance not found.\n";
                }
            }
            else if (strcmp(choice, "3") == 0) {
                std::cout << "--- MANAGE STORE SALES ---\n";
                std::cout << "1. Discount specific product\n";
                std::cout << "2. Discount entire brand\n";
                std::cout << "3. Clearance Sale (Low stock items)\n";
                std::cout << "4. Remove discount from product\n";
                std::cout << "5. Clear ALL store discounts\n";
                std::cout << "> ";
                char sChoice; std::cin >> sChoice; std::cin.ignore(10000, '\n');

                if (sChoice == '1') {
                    char fname[128]; double d;
                    std::cout << "Fragrance Name: "; std::cin >> fname;
                    std::cout << "Discount Percentage (0-100): "; std::cin >> d;
                    if (std::cin.fail() || d < 0 || d > 100) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "[!] Invalid discount percentage.\n";
                        continue;
                    }
                    std::cin.ignore(10000, '\n');
                    Fragrance* f = findFragrance(fname);
                    if (f) { f->setSaleDiscount(d); std::cout << "[✓] Sale applied!\n"; }
                    else std::cout << "[!] Fragrance not found.\n";
                }
                else if (sChoice == '2') {
                    int bInt; double d;
                    std::cout << "Brand (1-CHANEL, 2-DIOR, 3-TOM_FORD, 4-GUCCI): "; std::cin >> bInt;
                    std::cout << "Discount Percentage (0-100): "; std::cin >> d;
                    if (std::cin.fail() || bInt < 1 || bInt > 4 || d < 0 || d > 100) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "[!] Invalid input bounds.\n";
                        continue;
                    }
                    std::cin.ignore(10000, '\n');
                    Brand target = parseBrand(bInt);
                    int count = 0;
                    for (int i = 0; i < catalogCount; i++) {
                        if (!catalog[i]->getIsDeleted() && catalog[i]->getBrand() == target) {
                            catalog[i]->setSaleDiscount(d);
                            count++;
                        }
                    }
                    std::cout << "[✓] Applied " << d << "% sale to " << count << " active items.\n";
                }
                else if (sChoice == '3') {
                    int qtyThresh; double d;
                    std::cout << "Apply to items with quantity LESS or EQUAL to: "; std::cin >> qtyThresh;
                    std::cout << "Discount Percentage (0-100): "; std::cin >> d;
                    if (std::cin.fail() || d < 0 || d > 100 || qtyThresh < 0) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "[!] Invalid input bounds.\n";
                        continue;
                    }
                    std::cin.ignore(10000, '\n');
                    int count = 0;
                    for (int i = 0; i < catalogCount; i++) {
                        if (!catalog[i]->getIsDeleted() && catalog[i]->getQuantity() <= qtyThresh) {
                            catalog[i]->setSaleDiscount(d);
                            count++;
                        }
                    }
                    std::cout << "[✓] Applied " << d << "% clearance sale to " << count << " active items.\n";
                }
                else if (sChoice == '4') {
                    char fname[128];
                    std::cout << "Fragrance Name: "; std::cin >> fname;
                    std::cin.ignore(10000, '\n');
                    Fragrance* f = findFragrance(fname);
                    if (f) { f->setSaleDiscount(0); std::cout << "[✓] Discount removed.\n"; }
                    else std::cout << "[!] Fragrance not found.\n";
                }
                else if (sChoice == '5') {
                    for (int i = 0; i < catalogCount; i++) catalog[i]->setSaleDiscount(0);
                    std::cout << "[✓] All global sales have been removed.\n";
                }
            }
            else if (strcmp(choice, "4") == 0) {
                bool hasPending = false;
                std::cout << "--- PENDING ORDERS ---\n";
                for (int i = 0; i < purchCount; i++) {
                    if (allPurchases[i]->getStatus() == OrderStatus::PENDING) {
                        allPurchases[i]->show();
                        hasPending = true;
                    }
                }
                if (!hasPending) {
                    std::cout << "[!] No pending orders right now.\n";
                }
                else {
                    std::cout << "\nEnter Purchase ID to deliver (or 0 to abort): ";
                    int pId;
                    std::cin >> pId;
                    if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); }
                    else {
                        std::cin.ignore(10000, '\n');
                        if (pId != 0) {
                            Purchase* target = nullptr;
                            for (int i = 0; i < purchCount; i++) {
                                if (allPurchases[i]->getId() == pId && allPurchases[i]->getStatus() == OrderStatus::PENDING) {
                                    target = allPurchases[i];
                                    break;
                                }
                            }
                            if (target) {
                                target->setStatus(OrderStatus::DELIVERED);
                                std::cout << "[✓] Order #" << pId << " has been successfully delivered!\n";
                            }
                            else std::cout << "[!] Order not found or not pending.\n";
                        }
                    }
                }
            }
            else if (strcmp(choice, "5") == 0) {
                char uname[64];
                std::cout << "Enter username to block & delete: "; std::cin >> uname;
                std::cin.ignore(10000, '\n');

                if (equalsIgnoreCase(uname, loggedInUser->getUsername().c_str())) {
                    std::cout << "[!] You cannot block yourself. We need at least one admin.\n";
                    continue;
                }

                int foundIndex = -1;
                for (int i = 0; i < userCount; i++) {
                    if (equalsIgnoreCase(users[i]->getUsername().c_str(), uname)) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex != -1) {
                    if (users[foundIndex]->isAdmin()) {
                        std::cout << "[!] You cannot block another Admin.\n";
                    }
                    else {
                        if (blacklistCount == blacklistCapacity) resizeBlacklist();
                        blacklist[blacklistCount++] = String(users[foundIndex]->getUsername().c_str());

                        delete users[foundIndex];
                        for (int i = foundIndex; i < userCount - 1; i++) {
                            users[i] = users[i + 1];
                        }
                        users[userCount - 1] = nullptr;
                        userCount--;
                        std::cout << "[✓] User has been terminated and permanently blacklisted.\n";
                    }
                }
                else std::cout << "[!] User not found.\n";
            }
            else if (strcmp(choice, "6") == 0) {
                std::cout << "--- REGISTERED BUYERS ---\n";
                int bCount = 0;
                for (int i = 0; i < userCount; i++) {
                    if (!users[i]->isAdmin()) {
                        Buyer* b = static_cast<Buyer*>(users[i]);
                        std::cout << "ID: " << b->getId()
                            << " | Username: " << b->getUsername().c_str()
                            << " | Balance: " << b->getBalance() << " EUR"
                            << " | Strikes: " << b->getDeletedReviewsCount() << "/7\n";
                        bCount++;
                    }
                }
                if (bCount == 0) std::cout << "[!] No buyers registered yet.\n";
            }
            else if (strcmp(choice, "7") == 0) {
                char uname[64];
                std::cout << "Enter username to inspect: "; std::cin >> uname;
                std::cin.ignore(10000, '\n');

                bool found = false;
                for (int i = 0; i < userCount; i++) {
                    if (!users[i]->isAdmin() && equalsIgnoreCase(users[i]->getUsername().c_str(), uname)) {
                        static_cast<Buyer*>(users[i])->adminInspect();
                        found = true;
                        break;
                    }
                }
                if (!found) std::cout << "[!] Buyer not found.\n";
            }
            else if (strcmp(choice, "8") == 0) {
                char fname[128];
                std::cout << "Enter fragrance name: "; std::cin >> fname;
                std::cin.ignore(10000, '\n');

                Fragrance* f = findFragrance(fname);
                if (!f) {
                    std::cout << "[!] Fragrance not found.\n";
                }
                else {
                    f->printReviews();
                    if (f->getReviewCount() > 0) {
                        std::cout << "\nEnter Review ID to delete (or 0 to cancel): ";
                        int rId; std::cin >> rId;
                        if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); }
                        else {
                            std::cin.ignore(10000, '\n');
                            if (rId != 0) {
                                String authorName;
                                bool foundRev = false;
                                for (int i = 0; i < f->getReviewCount(); i++) {
                                    if (f->getReview(i)->getId() == rId) {
                                        authorName = f->getReview(i)->getAuthor();
                                        foundRev = true;
                                        break;
                                    }
                                }

                                if (foundRev) {
                                    f->removeReview(rId);
                                    std::cout << "[✓] Review deleted.\n";

                                    int bIndex = -1;
                                    for (int i = 0; i < userCount; i++) {
                                        if (!users[i]->isAdmin() && equalsIgnoreCase(users[i]->getUsername().c_str(), authorName.c_str())) {
                                            bIndex = i;
                                            break;
                                        }
                                    }

                                    if (bIndex != -1) {
                                        Buyer* badBoy = static_cast<Buyer*>(users[bIndex]);
                                        badBoy->incrementDeletedReviews();
                                        std::cout << "[!] User '" << authorName.c_str() << "' now has "
                                            << badBoy->getDeletedReviewsCount() << "/7 strikes.\n";

                                        if (badBoy->getDeletedReviewsCount() >= 7) {
                                            std::cout << "\n[!!!] STRIKE LIMIT REACHED. Banning user '" << authorName.c_str() << "'...\n";

                                            if (blacklistCount == blacklistCapacity) resizeBlacklist();
                                            blacklist[blacklistCount++] = String(authorName.c_str());

                                            delete users[bIndex];
                                            for (int i = bIndex; i < userCount - 1; i++) {
                                                users[i] = users[i + 1];
                                            }
                                            users[userCount - 1] = nullptr;
                                            userCount--;
                                        }
                                    }
                                }
                                else {
                                    std::cout << "[!] Review ID not found.\n";
                                }
                            }
                        }
                    }
                }
            }
            else if (strcmp(choice, "9") == 0) {
                char fname[128];
                std::cout << "Enter fragrance name to permanently delete: "; std::cin >> fname;
                std::cin.ignore(10000, '\n');

                Fragrance* f = findFragrance(fname);
                if (f) {
                    f->markAsDeleted();
                    for (int i = 0; i < userCount; i++) {
                        if (!users[i]->isAdmin()) {
                            Buyer* b = static_cast<Buyer*>(users[i]);
                            while (b->removeFromCart(f->getName().c_str()));
                            b->removeFromWishlist(f->getName().c_str());
                        }
                    }
                    std::cout << "[✓] Fragrance erased from catalog and all active carts.\n";
                }
                else {
                    std::cout << "[!] Fragrance not found.\n";
                }
            }
            else if (strcmp(choice, "10") == 0) {
                loggedInUser = nullptr;
                std::cout << "[✓] Admin logged out.\n";
            }
            else {
                std::cout << "[!] Invalid option.\n";
            }
        }

        else {
            Buyer* b = static_cast<Buyer*>(loggedInUser);

            if (strcmp(choice, "2") == 0) {
                char name[128]; int qty;
                std::cout << "Enter fragrance name to buy: "; std::cin >> name;
                std::cout << "How many?: "; std::cin >> qty;

                if (std::cin.fail() || qty <= 0) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid quantity format!\n";
                }
                else {
                    std::cin.ignore(10000, '\n');
                    Fragrance* f = findFragrance(name);
                    if (f) {
                        int alreadyInCart = 0;
                        for (int i = 0; i < b->getCartCount(); i++) if (b->getCartItem(i) == f) alreadyInCart++;

                        if (f->getQuantity() == 0) std::cout << "[!] Sorry, '" << f->getName().c_str() << "' is out of stock.\n";
                        else if (f->getQuantity() - alreadyInCart < qty) {
                            std::cout << "[!] Not enough stock! We have " << f->getQuantity()
                                << " total, but you already grabbed " << alreadyInCart << ".\n";
                        }
                        else {
                            for (int i = 0; i < qty; i++) b->addToCart(f);
                            std::cout << "[✓] Added " << qty << "x " << f->getName().c_str() << " to cart.\n";
                        }
                    }
                    else std::cout << "[!] Fragrance not found.\n";
                }
            }
            else if (strcmp(choice, "3") == 0) {
                b->viewCart();
                if (b->getCartCount() > 0) {
                    char name[128]; int qty;
                    std::cout << "Enter fragrance name to remove: "; std::cin >> name;
                    std::cout << "How many to remove?: "; std::cin >> qty;

                    if (std::cin.fail() || qty <= 0) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "[!] Invalid quantity.\n";
                    }
                    else {
                        std::cin.ignore(10000, '\n');
                        int removedCount = 0;
                        for (int i = 0; i < qty; i++) {
                            if (b->removeFromCart(name)) removedCount++;
                            else break;
                        }
                        if (removedCount > 0) std::cout << "[✓] Removed " << removedCount << "x from cart.\n";
                        else std::cout << "[!] Not in your cart.\n";
                    }
                }
            }
            else if (strcmp(choice, "4") == 0) {
                b->viewCart();
                if (b->getCartCount() > 0) {
                    std::cout << "\nProceed to checkout? (y/n): ";
                    char ans; std::cin >> ans; std::cin.ignore(10000, '\n');
                    if (ans == 'y' || ans == 'Y') handleCheckout();
                    else {
                        std::cout << "Empty the cart instead? (y/n): ";
                        std::cin >> ans; std::cin.ignore(10000, '\n');
                        if (ans == 'y' || ans == 'Y') { b->emptyCart(); std::cout << "[✓] Cart emptied.\n"; }
                    }
                }
            }
            else if (strcmp(choice, "5") == 0) {
                std::cout << "\n--- YOUR WISHLIST ---\n";
                if (b->getWishlistCount() == 0) {
                    std::cout << " [!] Empty.\n";
                }
                else {
                    for (int i = 0; i < b->getWishlistCount(); i++) {
                        std::cout << " -> " << b->getWishlistItem(i).c_str() << "\n";
                    }
                }
                std::cout << "\nOptions: [1] Add  [2] Remove  [0] Back\n> ";
                char wChoice;
                std::cin >> wChoice;
                std::cin.ignore(10000, '\n');

                if (wChoice == '1') {
                    std::cout << "Enter fragrance name to add: ";
                    char wName[128];
                    std::cin >> wName;
                    std::cin.ignore(10000, '\n');
                    Fragrance* f = findFragrance(wName);
                    if (f) {
                        b->addToWishlist(f->getName().c_str());
                    }
                    else {
                        std::cout << "[!] Fragrance not found in catalog.\n";
                    }
                }
                else if (wChoice == '2') {
                    std::cout << "Enter fragrance name to remove: ";
                    char wName[128];
                    std::cin >> wName;
                    std::cin.ignore(10000, '\n');
                    if (b->removeFromWishlist(wName)) {
                        std::cout << "[✓] Removed from wishlist.\n";
                    }
                    else {
                        std::cout << "[!] Not in your wishlist.\n";
                    }
                }
            }
            else if (strcmp(choice, "6") == 0) {
                double amount;
                std::cout << "Amount to add (EUR): "; std::cin >> amount;
                if (std::cin.fail() || amount <= 0) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid amount.\n";
                }
                else {
                    std::cin.ignore(10000, '\n');
                    b->addToBalance(amount);
                    std::cout << "[✓] Account funded! New balance: " << b->getBalance() << " EUR.\n";
                }
            }
            else if (strcmp(choice, "7") == 0) {
                b->viewPurchases();
                std::cout << "\nEnter Purchase ID to cancel (or 0 to go back): ";
                int pId;
                std::cin >> pId;
                if (std::cin.fail()) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "[!] Invalid input.\n";
                }
                else {
                    std::cin.ignore(10000, '\n');
                    if (pId != 0) {
                        Purchase* target = nullptr;
                        for (int i = 0; i < purchCount; i++) {
                            if (allPurchases[i]->getId() == pId && allPurchases[i]->getUserId() == b->getId()) {
                                target = allPurchases[i];
                                break;
                            }
                        }

                        if (target) {
                            if (target->getStatus() == OrderStatus::PENDING) {
                                target->setStatus(OrderStatus::CANCELED);
                                b->addToBalance(target->getTotalPrice());

                                for (int i = 0; i < target->getFragCount(); i++) {
                                    target->getFragrance(i)->addQuantity(1);
                                }
                                std::cout << "[✓] Order #" << pId << " canceled! Refunded " << target->getTotalPrice() << " EUR to your wallet.\n";
                            }
                            else {
                                std::cout << "[!] You can only cancel PENDING orders.\n";
                            }
                        }
                        else {
                            std::cout << "[!] Order not found or doesn't belong to you.\n";
                        }
                    }
                }
            }
            else if (strcmp(choice, "8") == 0) {
                if (b->getDiscountCount() == 0) std::cout << "[!] You have no vouchers. Buy something to earn one!\n";
                else {
                    std::cout << "--- Your Vouchers ---\n";
                    for (int i = 0; i < b->getDiscountCount(); i++) b->getDiscount(i)->print();
                }
            }
            else if (strcmp(choice, "9") == 0) {
                b->viewPurchases();
                std::cout << "\nName of fragrance to review: ";
                char name[128]; std::cin >> name;
                std::cin.ignore(10000, '\n');

                Fragrance* f = findFragrance(name);
                if (f) {
                    if (b->canReview(f)) {
                        std::cout << "Rating (1-5): ";
                        int rating; std::cin >> rating;
                        if (std::cin.fail() || rating < 1 || rating > 5) {
                            std::cin.clear(); std::cin.ignore(10000, '\n');
                            std::cout << "[!] Invalid rating. Must be between 1 and 5.\n";
                        }
                        else {
                            std::cin.ignore(10000, '\n');
                            std::cout << "Comment: ";
                            char comm[1024];
                            std::cin.getline(comm, 1024);

                            Review* r = new Review(nextReviewId++, b->getUsername().c_str(), comm, rating);
                            f->addReview(r);
                            std::cout << "[✓] Review published!\n";
                        }
                    }
                    else std::cout << "[!] You can only review items you've actually bought (1 review per purchase).\n";
                }
                else std::cout << "[!] Fragrance not found.\n";
            }
            else if (strcmp(choice, "10") == 0) {
                handleRecommend();
            }
            else if (strcmp(choice, "11") == 0) {
                loggedInUser = nullptr;
                std::cout << "[✓] Logged out successfully.\n";
            }
            else if (strcmp(choice, "1") != 0) {
                std::cout << "[!] Invalid option. Type a number from the menu.\n";
            }
        }

        waitForKey();
    }
}