#include "String.h"
#include <cstring>
#pragma warning(disable:4996)

void String::copyFrom(const String& other) {
    size = other.size;
    data = new char[size + 1];
    strcpy(data, other.data);
}

void String::free() {
    delete[] data;
}

String::String() {
    size = 0;
    data = new char[1];
    data[0] = '\0';
}

String::String(const char* str) {
    if (!str) {
        size = 0;
        data = new char[1];
        data[0] = '\0';
    }
    else {
        size = strlen(str);
        data = new char[size + 1];
        strcpy(data, str);
    }
}

String::String(const String& other) {
    copyFrom(other);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

String::~String() {
    free();
}

const char* String::c_str() const {
    return data;
}

int String::length() const {
    return size;
}

bool String::operator==(const String& other) const {
    return strcmp(data, other.data) == 0;
}