#pragma once
#include "Discount.h"

class BrandDiscount : public Discount {
private:
    Brand targetBrand;

public:
    BrandDiscount(int id, double percent, Brand brand);

    double apply(double currentPrice, Brand brand) const override;
    Discount* clone() const override;
    void print() const override;

    Brand getTargetBrand() const { return targetBrand; }
};