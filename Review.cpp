#include "Review.h"
#include <iostream>

Review::Review(int rId, const char* auth, const char* comm, int rate)
    : reviewId(rId), author(auth), comment(comm) {
    if (rate < 1) rating = 1;
    else if (rate > 5) rating = 5;
    else rating = rate;
}

int Review::getId() const { return reviewId; }
int Review::getRating() const { return rating; }
const String& Review::getAuthor() const { return author; }
const String& Review::getComment() const { return comment; }

void Review::print() const {
    std::cout << "User " << author.c_str() << " rated it " << rating << "/5:\n";
    std::cout << "  \"" << comment.c_str() << "\"\n";
}