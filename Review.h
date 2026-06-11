#pragma once
#include "String.h"

class Review {
private:
    int reviewId;
    String author;
    String comment;
    int rating;

public:
    Review(int rId, const char* auth, const char* comm, int rate);

    int getId() const;
    int getRating() const;
    const String& getAuthor() const;
    const String& getComment() const;

    void print() const;
};