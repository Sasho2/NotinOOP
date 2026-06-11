#pragma once
#include "String.h"
#include "Review.h"
#include "Enums.h"

class Fragrance {
private:
    int fragranceId;
    String name;
    Brand brand;
    double price;
    FragranceFamily family;
    int quantity;

    Review** reviews;
    int reviewCount;
    int reviewCapacity;

    void resizeReviews();

public:
    Fragrance(int id, const char* n, Brand b, double p, FragranceFamily f, int q);
    ~Fragrance();

    Fragrance(const Fragrance&) = delete;
    Fragrance& operator=(const Fragrance&) = delete;

    int getId() const;
    const String& getName() const;
    Brand getBrand() const;
    double getPrice() const;
    FragranceFamily getFamily() const;
    int getQuantity() const;

    void addQuantity(int amount);
    bool decreaseQuantity();

    void addReview(Review* r);
    double getRating() const;

    int getReviewCount() const { return reviewCount; }
    Review* getReview(int index) const { return reviews[index]; }

    void printReviews() const;
    void print() const;
};