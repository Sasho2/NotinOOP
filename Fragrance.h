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
    double saleDiscount;
    FragranceFamily family;
    int quantity;
    bool isDeleted;

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
    double getDiscountedPrice() const;

    double getSaleDiscount() const;
    void setSaleDiscount(double percent);

    FragranceFamily getFamily() const;
    int getQuantity() const;

    void addQuantity(int amount);
    bool decreaseQuantity();

    bool getIsDeleted() const;
    void markAsDeleted();

    void addReview(Review* r);
    bool removeReview(int rId);
    double getRating() const;

    int getReviewCount() const { return reviewCount; }
    Review* getReview(int index) const { return reviews[index]; }

    int getReviewCountByUser(const char* username) const;

    void printReviews() const;
    void print() const;
};