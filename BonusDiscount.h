#pragma once
#include "Discount.h"

class BonusDiscount : public Discount {
private:
    double bonusAmount;

public:
    BonusDiscount(int id, double percent, double bonus);

    double apply(double currentPrice, Brand brand) const override;
    Discount* clone() const override;
    void print() const override;

    double getBonus() const { return bonusAmount; }
};