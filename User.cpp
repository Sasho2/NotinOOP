#include "User.h"

User::User(int id, const char* uname, const char* pass)
    : userId(id), username(uname), password(pass) {
}

int User::getId() const { return userId; }
const String& User::getUsername() const { return username; }
const String& User::getPassword() const { return password; }

bool User::checkPassword(const char* pass) const {
    return password == String(pass);
}