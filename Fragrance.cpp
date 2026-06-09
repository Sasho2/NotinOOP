#include "Fragrance.h"

Fragrance::Fragrance(int id, const char* n, Brand b, double p, FragranceFamily f, int q)
    : fragranceId(id), name(n), brand(b), price(p), family(f), quantity(q) {
}

int Fragrance::getId() const { return fragranceId; }
const String& Fragrance::getName() const { return name; }
Brand Fragrance::getBrand() const { return brand; }
double Fragrance::getPrice() const { return price; }
FragranceFamily Fragrance::getFamily() const { return family; }
int Fragrance::getQuantity() const { return quantity; }

void Fragrance::addQuantity(int amount) {
    if (amount > 0) quantity += amount;
}

bool Fragrance::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
        return true;
    }
    return false;
}