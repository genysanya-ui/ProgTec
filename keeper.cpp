#include "keeper.h"
#include "exception.h"
#include "parent.h"
#include "child.h"
#include "spouse.h"

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
        ofs << items[i]->getType() << "\n";
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
    ifs.ignore();
    for (int i = 0; i < n; ++i) {
        char type[32];
        ifs.getline(type, sizeof(type));
        Base* item = nullptr;
        if (strcmp(type, "Parent") == 0) {
            item = new Parent();
        } else if (strcmp(type, "Child") == 0) {
            item = new Child();
        } else if (strcmp(type, "Spouse") == 0) {
            item = new Spouse();
        } else {
            throw FileException("Unknown type: " + std::string(type));
        }
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

void Keeper::printByType(std::ostream& os, const char type) const {
    if (size == 0) {
        throw EmptyKeeperException("No items to print.");
    }
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (items[i]->getType()[0] == type) {
            os << "Item " << i << ":" << std::endl;
            items[i]->print(os);
            os << std::endl;
            found = true;
        }
    }
    if (!found) {
        os << "No items of type " << type << " found." << std::endl;
    }
}