#include "NotinOOP.h"
#include <iostream>
#include <cstring>

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
        std::cout << "\n======================================\n";
        std::cout << "             STORE CATALOG            \n";
        std::cout << "======================================\n";
        if (catalogCount == 0) {
            std::cout << " [!] The shelves are empty.\n";
        }
        else {
            for (int i = 0; i < catalogCount; i++) {
                std::cout << " -> " << catalog[i]->getName().c_str()
                    << " | " << brandToString(catalog[i]->getBrand())
                    << " | Price: " << catalog[i]->getPrice() << " EUR"
                    << " | Qty: " << catalog[i]->getQuantity() << "\n";
            }
        }
        std::cout << "======================================\n";

        if (!loggedInUser) {
            std::cout << "\n [ Guest ]\n";
            std::cout << " 1. Login\n";
            std::cout << " 2. Register\n";
            std::cout << " 0. Exit\n> ";

            std::cin >> choice;
            if (strcmp(choice, "0") == 0) break;

            if (strcmp(choice, "1") == 0) {
                char user[64], pass[64];
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;

                bool found = false;
                for (int i = 0; i < userCount; i++) {
                    if (users[i]->getUsername() == String(user) && users[i]->checkPassword(pass)) {
                        loggedInUser = users[i];
                        found = true;
                        std::cout << "[Success] Logged in!\n";
                        break;
                    }
                }
                if (!found) std::cout << "[Error] Wrong credentials.\n";
            }
            else if (strcmp(choice, "2") == 0) {
                char user[64], pass[64];
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;

                bool exists = false;
                for (int i = 0; i < userCount; i++) {
                    if (users[i]->getUsername() == String(user)) { exists = true; break; }
                }

                if (exists) std::cout << "[Error] Username taken.\n";
                else {
                    if (userCount == userCapacity) resizeUsers();
                    users[userCount++] = new Buyer(userCount + 1, user, pass);
                    std::cout << "[Success] Registered!\n";
                }
            }
        }
        else if (loggedInUser->isAdmin()) {
            std::cout << "\n [ Admin: " << loggedInUser->getUsername().c_str() << " ]\n";
            std::cout << " 1. Add New Fragrance\n";
            std::cout << " 2. Logout\n";
            std::cout << " 0. Exit\n> ";

            std::cin >> choice;
            if (strcmp(choice, "0") == 0) break;

            if (strcmp(choice, "1") == 0) {
                char name[64];
                int bInt, fInt, qty;
                double price;

                std::cout << "Name (no spaces): "; std::cin >> name;
                std::cout << "Brand (1-CHANEL, 2-DIOR, 3-TOM_FORD, 4-GUCCI): "; std::cin >> bInt;
                std::cout << "Price (EUR): "; std::cin >> price;
                std::cout << "Family (1-CITRUS, 2-FLORAL, 3-WOODY, 4-ORIENTAL, 5-FRESH): "; std::cin >> fInt;
                std::cout << "Quantity: "; std::cin >> qty;

                if (catalogCount == catalogCapacity) resizeCatalog();
                catalog[catalogCount++] = new Fragrance(catalogCount + 1, name, parseBrand(bInt), price, parseFamily(fInt), qty);
                std::cout << "[Success] Added to catalog!\n";
            }
            else if (strcmp(choice, "2") == 0) {
                loggedInUser = nullptr;
                std::cout << "[Success] Logged out.\n";
            }
        }
        else {
            Buyer* b = static_cast<Buyer*>(loggedInUser);
            std::cout << "\n [ Buyer: " << b->getUsername().c_str() << " | Wallet: " << b->getBalance() << " EUR ]\n";
            std::cout << " 1. Add to Cart\n";
            std::cout << " 2. View Cart & Checkout\n";
            std::cout << " 3. Add Funds\n";
            std::cout << " 4. Logout\n";
            std::cout << " 0. Exit\n> ";

            std::cin >> choice;
            if (strcmp(choice, "0") == 0) break;

            if (strcmp(choice, "1") == 0) {
                char name[128];
                std::cout << "Enter fragrance name to buy: "; std::cin >> name;
                Fragrance* f = findFragrance(name);
                if (f) {
                    if (f->getQuantity() > 0) {
                        b->addToCart(f);
                        std::cout << "[Success] Added to cart.\n";
                    }
                    else std::cout << "[!] Out of stock.\n";
                }
                else std::cout << "[!] Not found.\n";
            }
            else if (strcmp(choice, "2") == 0) {
                b->viewCart();
                if (b->getCartCount() > 0) {
                    std::cout << "Proceed to checkout? (y/n): ";
                    char ans; std::cin >> ans;
                    if (ans == 'y') handleCheckout();
                }
            }
            else if (strcmp(choice, "3") == 0) {
                double amt;
                std::cout << "Amount (EUR): "; std::cin >> amt;
                b->addToBalance(amt);
                std::cout << "[Success] Funds added.\n";
            }
            else if (strcmp(choice, "4") == 0) {
                loggedInUser = nullptr;
                std::cout << "[Success] Logged out.\n";
            }
        }
    }
}