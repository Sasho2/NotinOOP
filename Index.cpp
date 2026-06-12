#include <iostream>
#include "NotinOOP.h"

int main() {
    NotinOOP store;

    store.loadFromFile("database.txt");

    store.run();

    return 0;
}