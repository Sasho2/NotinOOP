#include "Admin.h"

Admin::Admin(int id, const char* uname, const char* pass)
    : User(id, uname, pass) {
}

bool Admin::isAdmin() const {
    return true;
}