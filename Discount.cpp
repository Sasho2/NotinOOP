#include "Discount.h"

Discount::Discount(int dId, double p) : id(dId), percent(p) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
}

int Discount::getId() const { return id; }
double Discount::getPercent() const { return percent; }