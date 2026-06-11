#pragma once
#include "User.h"
#include "Fragrance.h"
#include "Purchase.h"

class Buyer : public User {
private:
    double balance;

    Fragrance** cart;
    int cartCount;
    int cartCapacity;

    Purchase** purchases;
    int purchCount;
    int purchCapacity;

    void resizeCart();
    void resizePurchases();

public:
    Buyer(int id, const char* uname, const char* pass);
    ~Buyer() override;

    bool isAdmin() const override;

    void addToBalance(double amount);
    double getBalance() const;
    void deductBalance(double amount);

    void addToCart(Fragrance* f);
    bool removeFromCart(const char* fName);
    void viewCart() const;
    void emptyCart();

    void addPurchase(Purchase* p);
    void viewPurchases() const;

    int getCartCount() const { return cartCount; }
    Fragrance* getCartItem(int index) const { return cart[index]; }
};