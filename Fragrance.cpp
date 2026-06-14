#include "Fragrance.h"
#include <iostream>
#include <iomanip>
#include <cctype>

static bool equalsIgnoreCase(const char* a, const char* b) {
    if (!a || !b) return false;
    for (; *a && *b; a++, b++) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return false;
    }
    return *a == *b;
}

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
    : fragranceId(id), name(n), brand(b), price(p), saleDiscount(0.0), family(f), quantity(q), isDeleted(false),
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

double Fragrance::getDiscountedPrice() const {
    if (saleDiscount <= 0) return price;
    return price - (price * (saleDiscount / 100.0));
}

double Fragrance::getSaleDiscount() const { return saleDiscount; }
void Fragrance::setSaleDiscount(double percent) {
    if (percent < 0) saleDiscount = 0;
    else if (percent > 100) saleDiscount = 100;
    else saleDiscount = percent;
}

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

bool Fragrance::getIsDeleted() const { return isDeleted; }
void Fragrance::markAsDeleted() { isDeleted = true; }

void Fragrance::addReview(Review* r) {
    if (reviewCount == reviewCapacity) {
        resizeReviews();
    }
    reviews[reviewCount++] = r;
}

bool Fragrance::removeReview(int rId) {
    for (int i = 0; i < reviewCount; i++) {
        if (reviews[i]->getId() == rId) {
            delete reviews[i];
            reviews[i] = reviews[reviewCount - 1];
            reviews[reviewCount - 1] = nullptr;
            reviewCount--;
            return true;
        }
    }
    return false;
}

double Fragrance::getRating() const {
    if (reviewCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < reviewCount; i++) {
        sum += reviews[i]->getRating();
    }
    return sum / reviewCount;
}

int Fragrance::getReviewCountByUser(const char* username) const {
    int count = 0;
    for (int i = 0; i < reviewCount; i++) {
        if (equalsIgnoreCase(reviews[i]->getAuthor().c_str(), username)) count++;
    }
    return count;
}

void Fragrance::printReviews() const {
    if (isDeleted) {
        std::cout << "[!] This fragrance has been discontinued.\n";
        return;
    }
    std::cout << "\n--- Reviews for " << name.c_str() << " ---\n";
    std::cout << std::setprecision(2) << "Average Rating: " << getRating() << std::setprecision(6) << " / 5.0\n";
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
    if (isDeleted) return;
    std::cout << "--- " << name.c_str() << " (" << brandToString(brand) << ") ---\n"
        << "Family: " << familyToString(family) << " | Price: " << getDiscountedPrice()
        << " | Quantity: " << quantity << " | Avg Rating: " << getRating() << "/5\n";
}