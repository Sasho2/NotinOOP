#include "BrandDiscount.h"
#include <iostream>

BrandDiscount::BrandDiscount(int id, double percent, Brand brand)
    : Discount(id, percent), targetBrand(brand) {
}

double BrandDiscount::apply(double currentPrice, Brand brand) const {
    if (brand == targetBrand) {
        return currentPrice - (currentPrice * (discountPercent / 100.0));
    }
    return currentPrice;
}

Discount* BrandDiscount::clone() const {
    return new BrandDiscount(*this);
}

void BrandDiscount::print() const {
    std::cout << "[Brand Discount ID: " << discountId << "] -"
        << discountPercent << "% for " << brandToString(targetBrand) << "\n";
}