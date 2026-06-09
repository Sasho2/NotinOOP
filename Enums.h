#pragma once

enum class Brand {
    CHANEL,
    DIOR,
    TOM_FORD,
    GUCCI,
    UNKNOWN
};

enum class FragranceFamily {
    CITRUS,
    FLORAL,
    WOODY,
    ORIENTAL,
    FRESH
};

enum class OrderStatus {
    PENDING,
    DELIVERED,
    CANCELED
};

inline const char* brandToString(Brand b) {
    switch (b) {
    case Brand::CHANEL: return "CHANEL";
    case Brand::DIOR: return "DIOR";
    case Brand::TOM_FORD: return "TOM_FORD";
    case Brand::GUCCI: return "GUCCI";
    default: return "UNKNOWN";
    }
}

inline const char* familyToString(FragranceFamily f) {
    switch (f) {
    case FragranceFamily::CITRUS: return "CITRUS";
    case FragranceFamily::FLORAL: return "FLORAL";
    case FragranceFamily::WOODY: return "WOODY";
    case FragranceFamily::ORIENTAL: return "ORIENTAL";
    default: return "FRESH";
    }
}