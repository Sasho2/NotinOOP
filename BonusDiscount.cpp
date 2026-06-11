#include "BonusDiscount.h"
#include <iostream>

BonusDiscount::BonusDiscount(int dId, double p, double bonus)
    : Discount(dId, p), flatBonus(bonus) {
}

double BonusDiscount::getBonus() const { return flatBonus; }

double BonusDiscount::apply(double currentPrice, Brand b) const {
    double afterPercent = currentPrice - (currentPrice * (percent / 100.0));
    double finalPrice = afterPercent - flatBonus;
    return (finalPrice < 0) ? 0 : finalPrice;
}

void BonusDiscount::print() const {
    std::cout << "[Voucher #" << id << "] -" << percent << "% AND -" << flatBonus << " EUR flat bonus!\n";
}