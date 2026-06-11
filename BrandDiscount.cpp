#include "BrandDiscount.h"
#include <iostream>

BrandDiscount::BrandDiscount(int dId, double p, Brand target)
    : Discount(dId, p), targetBrand(target) {
}

Brand BrandDiscount::getTargetBrand() const { return targetBrand; }

double BrandDiscount::apply(double currentPrice, Brand b) const {
    if (b == targetBrand) {
        return currentPrice - (currentPrice * (percent / 100.0));
    }
    return currentPrice;
}

void BrandDiscount::print() const {
    std::cout << "[Voucher #" << id << "] -" << percent << "% ONLY for " << brandToString(targetBrand) << "!\n";
}