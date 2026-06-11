#pragma once
#include "Discount.h"

class BrandDiscount : public Discount {
private:
    Brand targetBrand;

public:
    BrandDiscount(int dId, double p, Brand target);

    Brand getTargetBrand() const;
    double apply(double currentPrice, Brand b) const override;
    void print() const override;
};