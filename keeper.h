// Keeper - класс для хранения, сохранения и редактирования данных
#pragma once
#include "base.h"
#include <fstream>
#include <string>

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
};