#include "NotinOOP.h"

void NotinOOP::resizeUsers() {
    userCapacity = (userCapacity == 0) ? 2 : userCapacity * 2;
    User** temp = new User * [userCapacity];
    for (int i = 0; i < userCount; i++) temp[i] = users[i];
    delete[] users;
    users = temp;
}

NotinOOP::NotinOOP() : users(nullptr), userCount(0), userCapacity(0), loggedInUser(nullptr) {}

NotinOOP::~NotinOOP() {
    for (int i = 0; i < userCount; i++) delete users[i];
    delete[] users;
}