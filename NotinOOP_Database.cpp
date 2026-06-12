#include "NotinOOP.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <fstream>
#include <iostream>

void NotinOOP::saveToFile(const char* filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "[!] System Error: Could not open file for writing.\n";
        return;
    }

    out << catalogCount << "\n";
    for (int i = 0; i < catalogCount; i++) {
        out << catalog[i]->getId() << " "
            << catalog[i]->getName().c_str() << " "
            << (int)catalog[i]->getBrand() << " "
            << catalog[i]->getPrice() << " "
            << catalog[i]->getSaleDiscount() << " "
            << (int)catalog[i]->getFamily() << " "
            << catalog[i]->getQuantity() << " "
            << catalog[i]->getIsDeleted() << "\n";

        out << catalog[i]->getReviewCount() << "\n";
        for (int r = 0; r < catalog[i]->getReviewCount(); r++) {
            Review* rev = catalog[i]->getReview(r);
            out << rev->getId() << " "
                << rev->getAuthor().c_str() << " "
                << rev->getRating() << "\n"
                << rev->getComment().c_str() << "\n";
        }
    }

    out << userCount << "\n";
    for (int i = 0; i < userCount; i++) {
        if (users[i]->isAdmin()) {
            out << "A " << users[i]->getId() << " " << users[i]->getUsername().c_str() << " " << users[i]->getPassword().c_str() << "\n";
        }
        else {
            Buyer* b = static_cast<Buyer*>(users[i]);
            out << "B " << b->getId() << " " << b->getUsername().c_str() << " " << b->getPassword().c_str() << " " << b->getBalance() << " " << b->getDeletedReviewsCount() << " ";

            out << b->getCartCount() << " ";
            for (int j = 0; j < b->getCartCount(); j++) {
                out << b->getCartItem(j)->getId() << " ";
            }

            out << b->getDiscountCount() << " ";
            for (int j = 0; j < b->getDiscountCount(); j++) {
                Discount* d = b->getDiscount(j);
                if (BonusDiscount* bd = dynamic_cast<BonusDiscount*>(d)) {
                    out << "1 " << bd->getId() << " " << bd->getPercent() << " " << bd->getBonus() << " ";
                }
                else if (BrandDiscount* brd = dynamic_cast<BrandDiscount*>(d)) {
                    out << "2 " << brd->getId() << " " << brd->getPercent() << " " << (int)brd->getTargetBrand() << " ";
                }
            }

            out << b->getWishlistCount() << " ";
            for (int j = 0; j < b->getWishlistCount(); j++) {
                out << b->getWishlistItem(j).c_str() << " ";
            }
            out << "\n";
        }
    }

    out << purchCount << "\n";
    for (int i = 0; i < purchCount; i++) {
        Purchase* p = allPurchases[i];
        out << p->getId() << " "
            << p->getUserId() << " "
            << (int)p->getStatus() << " "
            << p->getFragCount() << " "
            << p->getTotalPrice() << " ";

        for (int j = 0; j < p->getFragCount(); j++) {
            out << p->getFragrance(j)->getId() << " ";
        }
        out << "\n";
    }

    out << blacklistCount << "\n";
    for (int i = 0; i < blacklistCount; i++) {
        out << blacklist[i].c_str() << "\n";
    }

    out.close();
}

void NotinOOP::loadFromFile(const char* filename) {
    std::ifstream in(filename);
    if (!in) return;

    int cCount;
    if (!(in >> cCount)) return;
    for (int i = 0; i < cCount; i++) {
        int id, brandInt, familyInt, qty;
        char name[64];
        double price, sDiscount;
        bool isDel;
        in >> id >> name >> brandInt >> price >> sDiscount >> familyInt >> qty >> isDel;

        if (catalogCount == catalogCapacity) resizeCatalog();
        Fragrance* newF = new Fragrance(id, name, (Brand)brandInt, price, (FragranceFamily)familyInt, qty);
        newF->setSaleDiscount(sDiscount);
        if (isDel) newF->markAsDeleted();

        catalog[catalogCount++] = newF;

        int rCount;
        in >> rCount;
        for (int r = 0; r < rCount; r++) {
            int rId, rRate;
            char author[64];
            in >> rId >> author >> rRate;
            in.ignore();
            char commBuf[1024];
            in.getline(commBuf, 1024);

            catalog[catalogCount - 1]->addReview(new Review(rId, author, commBuf, rRate));
            if (rId >= nextReviewId) nextReviewId = rId + 1;
        }
    }

    int uCount;
    in >> uCount;
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
            double balance = 0.0;
            int delRev = 0;
            in >> balance >> delRev;
            Buyer* b = new Buyer(id, name, pass);
            b->addToBalance(balance);
            b->setDeletedReviewsCount(delRev);

            int cartItems;
            in >> cartItems;
            for (int j = 0; j < cartItems; j++) {
                int fragId;
                in >> fragId;
                for (int k = 0; k < catalogCount; k++) {
                    if (catalog[k]->getId() == fragId) {
                        b->addToCart(catalog[k]);
                        break;
                    }
                }
            }

            int discCount = 0;
            if (in >> discCount) {
                for (int j = 0; j < discCount; j++) {
                    int dType, dId;
                    double percent;
                    in >> dType >> dId >> percent;
                    if (dType == 1) {
                        double bonus;
                        in >> bonus;
                        b->addDiscount(new BonusDiscount(dId, percent, bonus));
                    }
                    else if (dType == 2) {
                        int brandInt;
                        in >> brandInt;
                        b->addDiscount(new BrandDiscount(dId, percent, (Brand)brandInt));
                    }
                }
            }

            int wishCount = 0;
            if (in >> wishCount) {
                for (int j = 0; j < wishCount; j++) {
                    char wName[128];
                    in >> wName;
                    b->addToWishlist(wName);
                }
            }

            users[userCount++] = b;
        }
    }

    int pCount;
    if (in >> pCount) {
        for (int i = 0; i < pCount; i++) {
            int pId, uId, statusInt, fCount;
            double tPrice;
            in >> pId >> uId >> statusInt >> fCount >> tPrice;

            Purchase* p = new Purchase(pId, uId);
            p->setStatus((OrderStatus)statusInt);

            for (int j = 0; j < fCount; j++) {
                int fragId;
                in >> fragId;

                Fragrance* loadedFrag = nullptr;
                for (int k = 0; k < catalogCount; k++) {
                    if (catalog[k]->getId() == fragId) {
                        loadedFrag = catalog[k];
                        break;
                    }
                }
                if (loadedFrag) p->addFragrance(loadedFrag, tPrice / fCount);
            }

            if (purchCapacity == purchCount) resizePurchases();
            allPurchases[purchCount++] = p;

            for (int k = 0; k < userCount; k++) {
                if (!users[k]->isAdmin() && users[k]->getId() == uId) {
                    static_cast<Buyer*>(users[k])->addPurchase(p);
                    break;
                }
            }
            if (pId >= nextPurchaseId) nextPurchaseId = pId + 1;
        }
    }

    int blCount = 0;
    if (in >> blCount) {
        for (int i = 0; i < blCount; i++) {
            char bName[64];
            in >> bName;
            if (blacklistCount == blacklistCapacity) resizeBlacklist();
            blacklist[blacklistCount++] = String(bName);
        }
    }
    in.close();
}