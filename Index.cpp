#include "NotinOOP.h"

int main() {
    NotinOOP store;

    store.loadFromFile("database.txt");

    store.run();

    store.saveToFile("database.txt");

    return 0;
}