#pragma once
#include "String.h"
#include "Enums.h"

class Fragrance {
private:
    int fragranceId;
    String name;
    Brand brand;
    double price;
    FragranceFamily family;
    int quantity;

public:
    Fragrance(int id, const char* n, Brand b, double p, FragranceFamily f, int q);

    int getId() const;
    const String& getName() const;
    Brand getBrand() const;
    double getPrice() const;
    FragranceFamily getFamily() const;
    int getQuantity() const;

    void addQuantity(int amount);
    bool decreaseQuantity();
};