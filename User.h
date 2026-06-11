#pragma once
#include "String.h"

class User {
protected:
    int userId;
    String username;
    String password;

public:
    User(int id, const char* uname, const char* pass)
        : userId(id), username(uname), password(pass) {
    }
    virtual ~User() = default;

    int getId() const { return userId; }
    const String& getUsername() const { return username; }
    bool checkPassword(const char* pass) const { return password == String(pass); }

    const String& getPassword() const { return password; }

    virtual bool isAdmin() const = 0;   
};