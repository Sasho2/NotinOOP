#pragma once
#include "Discount.h"

class BonusDiscount : public Discount {
private:
    double flatBonus;

public:
    BonusDiscount(int dId, double p, double bonus);

    double getBonus() const;
    double apply(double currentPrice, Brand b) const override;
    void print() const override;
};