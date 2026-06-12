#include "Discount.h"
#include <iostream>

Discount::Discount(int id, double percent) : discountId(id), discountPercent(percent) {}

int Discount::getId() const { return discountId; }
double Discount::getPercent() const { return discountPercent; }