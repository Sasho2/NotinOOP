#pragma once
#include <iostream>

class String {
private:
    char* data;
    int size;

    void copyFrom(const String& other);
    void free();

public:
    String();
    String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    const char* c_str() const;
    int length() const;

    bool operator==(const String& other) const;
};