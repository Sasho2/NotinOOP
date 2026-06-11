#pragma once
#include "Enums.h"

class Discount {
protected:
    int id;
    double percent;

public:
    Discount(int dId, double p);
    virtual ~Discount() = default;

    int getId() const;
    double getPercent() const;

    virtual double apply(double currentPrice, Brand b) const = 0;
    virtual void print() const = 0;
};