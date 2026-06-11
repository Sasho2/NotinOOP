#include "Purchase.h"
#include <iostream>

void Purchase::resizeFragrances() {
    fragCapacity = (fragCapacity == 0) ? 2 : fragCapacity * 2;
    Fragrance** temp = new Fragrance * [fragCapacity];
    for (int i = 0; i < fragCount; i++) temp[i] = fragrances[i];
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

int Purchase::getId() const { return purchaseId; }
int Purchase::getUserId() const { return userId; }
OrderStatus Purchase::getStatus() const { return status; }
void Purchase::setStatus(OrderStatus s) { status = s; }
int Purchase::getFragCount() const { return fragCount; }
Fragrance* Purchase::getFragrance(int index) const { return fragrances[index]; }
double Purchase::getTotalPrice() const { return totalPrice; }

void Purchase::addFragrance(Fragrance* f, double finalPrice) {
    if (fragCount == fragCapacity) resizeFragrances();
    fragrances[fragCount++] = f;
    totalPrice += finalPrice;
}

void Purchase::show() const {
    std::cout << "Order #" << purchaseId << " | Status: ";
    if (status == OrderStatus::PENDING) std::cout << "PENDING";
    else if (status == OrderStatus::DELIVERED) std::cout << "DELIVERED";
    else std::cout << "CANCELED";

    std::cout << " | Total: " << totalPrice << " EUR\n";
    for (int i = 0; i < fragCount; i++) {
        std::cout << "   - " << fragrances[i]->getName().c_str() << "\n";
    }
}