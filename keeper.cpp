#include "keeper.h"
#include "exception.h"
#include "familyMember.h"
#include <cstring>
#include <stdexcept>

Keeper::Keeper() : items(nullptr), size(0), capacity(0) {
    std::cout << "Keeper default constructor called" << std::endl;
    items = new Base*[capacity];
}

Keeper::Keeper(const Keeper& other) : items(nullptr), size(other.size), capacity(other.capacity) {
    std::cout << "Keeper copy constructor called" << std::endl;
    items = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        items[i] = other.items[i]->clone();
    }
}

Keeper& Keeper::operator=(const Keeper& other) {
    std::cout << "Keeper assignment operator called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete items[i];
        }
        delete[] items;

        size = other.size;
        capacity = other.capacity;
        items = new Base*[capacity];
        for (int i = 0; i < size; ++i) {
            items[i] = other.items[i]->clone();
        }
    }
    return *this;
}

Keeper::~Keeper() {
    std::cout << "Keeper destructor called" << std::endl;
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    delete[] items;
}

void Keeper::ensureCapacity(int newCapacity) {
    if (newCapacity <= capacity) return;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < size; ++i) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void Keeper::add(Base* item) {
    if (size >= capacity) {
        ensureCapacity(capacity == 0 ? 1 : capacity * 2);
    }
    items[size++] = item;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw IndexOutOfRangeException("Index " + std::to_string(index) + " is out of range.");
    }
    delete items[index];
    for (int i = index; i < size - 1; ++i) {
        items[i] = items[i + 1];
    }
    --size;
}

Base* Keeper::get(int index) const {
    if (index < 0 || index >= size) {
        throw IndexOutOfRangeException("Index " + std::to_string(index) + " is out of range.");
    }
    return items[index];
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw FileException("Could not open file " + filename + " for writing.");
    }
    ofs << size << "\n";
    for (int i = 0; i < size; ++i) {
        items[i]->save(ofs);
    }
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw FileException("Could not open file " + filename + " for reading.");
    }
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    delete[] items;
    size = 0;
    capacity = 2;
    items = new Base*[capacity];
    int n = 0;
    ifs >> n;
    if (ifs.fail()) {
        throw FileException("Invalid count in file");
    }
    ifs.ignore();
    for (int i = 0; i < n; ++i) {
        Base* item = new familyMember();
        item->load(ifs);
        add(item);
    }
}

void Keeper::printAll(std::ostream& os) const {
    if (size == 0) {
        throw EmptyKeeperException("No items to print.");
    }
    for (int i = 0; i < size; ++i) {
        os << "Item " << i << ":" << std::endl;
        items[i]->print(os);
        os << std::endl;
    }
}