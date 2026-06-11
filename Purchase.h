#pragma once
#include "Fragrance.h"
#include "Enums.h"

class Purchase {
private:
    int purchaseId;
    int userId;
    OrderStatus status;

    Fragrance** fragrances;
    int fragCount;
    int fragCapacity;
    double totalPrice;

    void resizeFragrances();

public:
    Purchase(int pId, int uId);
    ~Purchase();

    int getId() const;
    int getUserId() const;
    OrderStatus getStatus() const;
    void setStatus(OrderStatus s);

    int getFragCount() const;
    Fragrance* getFragrance(int index) const;
    double getTotalPrice() const;

    void addFragrance(Fragrance* f, double finalPrice);
    void show() const;
};