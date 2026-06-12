#pragma once
#include "Enums.h"

class Discount {
protected:
    int discountId;
    double discountPercent;

public:
    Discount(int id, double percent);
    virtual ~Discount() = default;

    virtual double apply(double currentPrice, Brand brand) const = 0;

    virtual Discount* clone() const = 0;

    int getId() const;
    double getPercent() const;
    virtual void print() const = 0;
};