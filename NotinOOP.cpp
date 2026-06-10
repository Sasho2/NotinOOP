#include "NotinOOP.h"
#include <iostream>
#include <cstring>

void NotinOOP::run() {
    if (userCount == 0) {
        resizeUsers();
        users[userCount++] = new Admin(1, "admin", "admin123");
    }

    char choice[10];

    while (true) {
        std::cout << "\n======================================\n";
        std::cout << "                 NOTINOOP                \n";
        std::cout << "======================================\n";

        if (!loggedInUser) {
            std::cout << "1. Login\n";
            std::cout << "2. Register\n";
            std::cout << "0. Exit\n> ";

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
                std::cout << "Choose Username: "; std::cin >> user;
                std::cout << "Choose Password: "; std::cin >> pass;

                bool exists = false;
                for (int i = 0; i < userCount; i++) {
                    if (users[i]->getUsername() == String(user)) { exists = true; break; }
                }

                if (exists) { std::cout << "[Error] Username taken.\n"; }
                else {
                    if (userCount == userCapacity) resizeUsers();
                    users[userCount++] = new Buyer(userCount + 1, user, pass);
                    std::cout << "[Success] Registered!\n";
                }
            }
        }
        else {
            std::cout << "Logged in as: " << loggedInUser->getUsername().c_str() << "\n";
            std::cout << "1. Logout\n";
            std::cout << "0. Exit\n> ";

            std::cin >> choice;
            if (strcmp(choice, "0") == 0) break;
            if (strcmp(choice, "1") == 0) {
                loggedInUser = nullptr;
                std::cout << "[Success] Logged out.\n";
            }
        }
    }
}