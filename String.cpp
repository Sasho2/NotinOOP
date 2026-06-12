#include "String.h"
#include <cstring>
#pragma warning(disable:4996)

void String::copyFrom(const char* str) {
    if (str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    else {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
}

void String::free() {
    delete[] data;
    data = nullptr;
    length = 0;
}

String::String() {
    copyFrom("");
}

String::String(const char* str) {
    copyFrom(str);
}

String::String(const String& other) {
    copyFrom(other.data);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other.data);
    }
    return *this;
}

String::~String() {
    free();
}

const char* String::c_str() const {
    return data;
}

size_t String::getLength() const {
    return length;
}

bool String::operator==(const String& other) const {
    return strcmp(data, other.data) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}