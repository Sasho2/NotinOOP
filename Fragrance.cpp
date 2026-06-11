#include "Fragrance.h"
#include <iostream>

void Fragrance::resizeReviews() {
    reviewCapacity = (reviewCapacity == 0) ? 2 : reviewCapacity * 2;
    Review** temp = new Review * [reviewCapacity];
    for (int i = 0; i < reviewCount; i++) {
        temp[i] = reviews[i];
    }
    delete[] reviews;
    reviews = temp;
}

Fragrance::Fragrance(int id, const char* n, Brand b, double p, FragranceFamily f, int q)
    : fragranceId(id), name(n), brand(b), price(p), family(f), quantity(q),
    reviews(nullptr), reviewCount(0), reviewCapacity(0) {
}

Fragrance::~Fragrance() {
    for (int i = 0; i < reviewCount; i++) {
        delete reviews[i];
    }
    delete[] reviews;
}

int Fragrance::getId() const { return fragranceId; }
const String& Fragrance::getName() const { return name; }
Brand Fragrance::getBrand() const { return brand; }
double Fragrance::getPrice() const { return price; }
FragranceFamily Fragrance::getFamily() const { return family; }
int Fragrance::getQuantity() const { return quantity; }

void Fragrance::addQuantity(int amount) {
    if (amount > 0) quantity += amount;
}

bool Fragrance::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
        return true;
    }
    return false;
}

void Fragrance::addReview(Review* r) {
    if (reviewCount == reviewCapacity) {
        resizeReviews();
    }
    reviews[reviewCount++] = r;
}

double Fragrance::getRating() const {
    if (reviewCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < reviewCount; i++) {
        sum += reviews[i]->getRating();
    }
    return sum / reviewCount;
}

void Fragrance::printReviews() const {
    std::cout << "\n--- Reviews for " << name.c_str() << " ---\n";
    std::cout << "Average Rating: " << getRating() << " / 5.0\n";
    if (reviewCount == 0) {
        std::cout << "[Info] No reviews yet.\n";
    }
    else {
        for (int i = 0; i < reviewCount; i++) {
            reviews[i]->print();
        }
    }
    std::cout << "-----------------------\n";
}

void Fragrance::print() const {
    std::cout << "--- " << name.c_str() << " (" << brandToString(brand) << ") ---\n"
        << "Family: " << familyToString(family) << " | Price: " << price
        << " | Quantity: " << quantity << " | Avg Rating: " << getRating() << "/5\n";
}