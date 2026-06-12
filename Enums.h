#pragma once

enum class Brand { CHANEL, DIOR, TOM_FORD, GUCCI, UNKNOWN };
enum class FragranceFamily { CITRUS, FLORAL, WOODY, ORIENTAL, FRESH };
enum class OrderStatus { PENDING, DELIVERED, CANCELED };

inline const char* brandToString(Brand b) {
    switch (b) {
    case Brand::CHANEL: return "Chanel";
    case Brand::DIOR: return "Dior";
    case Brand::TOM_FORD: return "Tom Ford";
    case Brand::GUCCI: return "Gucci";
    default: return "Unknown";
    }
}

inline const char* familyToString(FragranceFamily f) {
    switch (f) {
    case FragranceFamily::CITRUS: return "Citrus";
    case FragranceFamily::FLORAL: return "Floral";
    case FragranceFamily::WOODY: return "Woody";
    case FragranceFamily::ORIENTAL: return "Oriental";
    case FragranceFamily::FRESH: return "Fresh";
    default: return "Unknown";
    }
}

inline const char* statusToString(OrderStatus s) {
    switch (s) {
    case OrderStatus::PENDING: return "Pending";
    case OrderStatus::DELIVERED: return "Delivered";
    case OrderStatus::CANCELED: return "Canceled";
    default: return "Unknown";
    }
}