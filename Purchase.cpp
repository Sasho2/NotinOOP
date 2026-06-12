#include "Purchase.h"
#include <iostream>

void Purchase::resize() {
    fragCapacity = (fragCapacity == 0) ? 2 : fragCapacity * 2;
    Fragrance** temp = new Fragrance * [fragCapacity];
    for (int i = 0; i < fragCount; i++) {
        temp[i] = fragrances[i];
    }
    delete[] fragrances;
    fragrances = temp;
}

Purchase::Purchase(int pId, int uId)
    : purchaseId(pId), userId(uId), status(OrderStatus::PENDING),
    fragrances(nullptr), fragCount(0), fragCapacity(0), totalPrice(0.0) {
}

Purchase::~Purchase() {
    delete[] fragrances;
}

void Purchase::addFragrance(Fragrance* f, double finalPrice) {
    if (fragCount == fragCapacity) {
        resize();
    }
    fragrances[fragCount++] = f;
    totalPrice += finalPrice;
}

void Purchase::setStatus(OrderStatus s) { status = s; }
OrderStatus Purchase::getStatus() const { return status; }
int Purchase::getId() const { return purchaseId; }
int Purchase::getUserId() const { return userId; }

void Purchase::show() const {
    std::cout << ">>> Purchase ID: " << purchaseId << " | User ID: " << userId
        << " | Status: " << statusToString(status) << "\n";
    std::cout << "Items:\n";
    for (int i = 0; i < fragCount; i++) {
        std::cout << " - " << fragrances[i]->getName().c_str() << "\n";
    }
    std::cout << "Total Price: " << totalPrice << "lv.\n<<<\n";
}