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

    void resize();

public:
    Purchase(int pId, int uId);
    ~Purchase();

    Purchase(const Purchase&) = delete;
    Purchase& operator=(const Purchase&) = delete;

    void addFragrance(Fragrance* f, double finalPrice);

    void setStatus(OrderStatus s);
    OrderStatus getStatus() const;
    int getId() const;
    int getUserId() const;

    int getFragCount() const { return fragCount; }
    Fragrance* getFragrance(int index) const { return fragrances[index]; }
    double getTotalPrice() const { return totalPrice; }

    void show() const;
};