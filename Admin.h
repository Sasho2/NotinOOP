#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin(int id, const char* uname, const char* pass);
    bool isAdmin() const override;
};