// Keeper - кдасс для хранения, сохранения и редактироывния данных
#pragma once
#include "Base.h"
#include <fstream>

class Keeper {
    Base** items;
    int size;
    int capacity;
    void ensureCapacity(int newCapacity);
public:
    Keeper();
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();

    void add(Base* item);
    void remove(int index);
    Base* get(int index) const;
    int getSize() const {return size;};

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    void printAll(std::ostream& os) const;
    void printByType(std::ostream& os, const char type) const;
};