#include "NotinOOP.h"
#include <fstream>
#include <iostream>

void NotinOOP::saveToFile(const char* filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "[!] Неуспешно отваряне на файла за запис.\n";
        return;
    }

    out << catalogCount << "\n";
    for (int i = 0; i < catalogCount; i++) {
        out << catalog[i]->getId() << " "
            << catalog[i]->getName().c_str() << " "
            << (int)catalog[i]->getBrand() << " "
            << catalog[i]->getPrice() << " "
            << catalog[i]->getQuantity() << "\n";
    }

    out << userCount << "\n";
    for (int i = 0; i < userCount; i++) {
        if (users[i]->isAdmin()) {
            out << "A " << users[i]->getId() << " "
                << users[i]->getUsername().c_str() << " "
                << users[i]->getPassword().c_str() << "\n";
        }
        else {
            Buyer* b = static_cast<Buyer*>(users[i]);
            out << "B " << b->getId() << " "
                << b->getUsername().c_str() << " "
                << b->getPassword().c_str() << " "
                << b->getBalance() << "\n";
        }
    }
    out.close();
}

void NotinOOP::loadFromFile(const char* filename) {
    std::ifstream in(filename);
    if (!in) return;

    int cCount;
    if (!(in >> cCount)) return;
    for (int i = 0; i < cCount; i++) {
        int id, brandInt, qty;
        char name[64];
        double price;
        in >> id >> name >> brandInt >> price >> qty;

        if (catalogCount == catalogCapacity) resizeCatalog();
        catalog[catalogCount++] = new Fragrance(id, name, (Brand)brandInt, price, FragranceFamily::FRESH, qty);
    }

    int uCount;
    if (!(in >> uCount)) return;
    for (int i = 0; i < uCount; i++) {
        char type;
        int id;
        char name[64], pass[64];
        in >> type >> id >> name >> pass;

        if (userCount == userCapacity) resizeUsers();
        if (type == 'A') {
            users[userCount++] = new Admin(id, name, pass);
        }
        else {
            double balance;
            in >> balance;
            Buyer* b = new Buyer(id, name, pass);
            b->addToBalance(balance);
            users[userCount++] = b;
        }
    }
    in.close();
}