#pragma once
#include "String.h"

class User {
protected:
    int userId;
    String username;
    String password;

public:
    User(int id, const char* uname, const char* pass);
    virtual ~User() = default;

    int getId() const;
    const String& getUsername() const;
    const String& getPassword() const;
    bool checkPassword(const char* pass) const;

    virtual bool isAdmin() const = 0;
};