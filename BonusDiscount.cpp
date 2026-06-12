#include "BonusDiscount.h"
#include <iostream>

BonusDiscount::BonusDiscount(int id, double percent, double bonus)
    : Discount(id, percent), bonusAmount(bonus) {
}

double BonusDiscount::apply(double currentPrice, Brand brand) const {
    double newPrice = currentPrice - (currentPrice * (discountPercent / 100.0));
    newPrice -= bonusAmount;
    return (newPrice < 0) ? 0.0 : newPrice;
}

Discount* BonusDiscount::clone() const {
    return new BonusDiscount(*this);
}

void BonusDiscount::print() const {
    std::cout << "[Bonus Discount ID: " << discountId << "] -"
        << discountPercent << "% AND -" << bonusAmount << " EUR\n";
}