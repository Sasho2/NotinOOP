#pragma once
#include "User.h"
#include "Fragrance.h"
#include "Purchase.h"
#include "Discount.h"

class Buyer : public User {
private:
    Fragrance** cart;
    int cartCount;
    int cartCapacity;

    String* wishlist;
    int wishCount;
    int wishCapacity;

    Purchase** purchases;
    int purchCount;
    int purchCapacity;

    Discount** discounts;
    int discCount;
    int discCapacity;

    double balance;
    int deletedReviewsCount;

    void resizeCart();
    void resizeWishlist();
    void resizePurchases();
    void resizeDiscounts();

public:
    Buyer(int id, const char* uname, const char* pass);
    ~Buyer() override;

    bool isAdmin() const override;

    void addToBalance(double amount);
    double getBalance() const;
    void deductBalance(double amount);
    void addDiscount(Discount* d);

    void addToCart(Fragrance* f);
    bool removeFromCart(const char* fName);
    void viewCart() const;
    void emptyCart();

    void addToWishlist(const char* fName);
    bool removeFromWishlist(const char* fName);
    bool isInWishlist(const char* fName) const;

    void addPurchase(Purchase* p);
    void viewBought() const;
    void viewPurchases() const;

    bool canReview(Fragrance* f) const;
    bool hasBought(const char* fName) const;

    int getCartCount() const { return cartCount; }
    Fragrance* getCartItem(int index) const { return cart[index]; }

    int getDiscountCount() const { return discCount; }
    Discount* getDiscount(int index) const { return discounts[index]; }
    void removeDiscount(int index);

    int getWishlistCount() const { return wishCount; }
    const String& getWishlistItem(int index) const { return wishlist[index]; }

    int getDeletedReviewsCount() const { return deletedReviewsCount; }
    void setDeletedReviewsCount(int count) { deletedReviewsCount = count; }
    void incrementDeletedReviews() { deletedReviewsCount++; }
    void adminInspect() const;
};