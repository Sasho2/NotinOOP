#pragma once
#include <iostream>

class String {
private:
    char* data;
    size_t length;

    void copyFrom(const char* str);
    void free();

public:
    String();
    String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    const char* c_str() const;
    size_t getLength() const;

    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
};