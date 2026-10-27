#include "spouse.h"

Spouse::Spouse() : Person(), spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "Spouse default constructor called" << std::endl;
    copyStr(spouseName, "Unknown");
    copyStr(marriageDate, "Unknown");
    copyStr(childrenList, "None");
}

Spouse::Spouse(const char* name, const char* birthDate, const char* deathDate, int age, const char* spouseName, const char* marriageDate, const char* childrenList)
    : Person(name, birthDate, deathDate, age), spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "Spouse parameterized constructor called" << std::endl;
    copyStr(this->spouseName, spouseName);
    copyStr(this->marriageDate, marriageDate);
    copyStr(this->childrenList, childrenList);
}

Spouse::Spouse(const Spouse& other) : Person(other), spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "Spouse copy constructor called" << std::endl;
    copyStr(spouseName, other.spouseName);
    copyStr(marriageDate, other.marriageDate);
    copyStr(childrenList, other.childrenList);
}

Spouse& Spouse::operator=(const Spouse& other) {
    std::cout << "Spouse assignment operator called" << std::endl;
    if (this != &other) {
        Person::operator=(other);
        freeStr(spouseName);
        freeStr(marriageDate);
        freeStr(childrenList);
        copyStr(spouseName, other.spouseName);
        copyStr(marriageDate, other.marriageDate);
        copyStr(childrenList, other.childrenList);
    }
    return *this;
}

Spouse::~Spouse() {
    std::cout << "Spouse destructor called" << std::endl;
    freeStr(spouseName);
    freeStr(marriageDate);
    freeStr(childrenList);
}

void Spouse::setSpouseName(const char* spouseName) {
    freeStr(this->spouseName);
    copyStr(this->spouseName, spouseName);
}

void Spouse::setMarriageDate(const char* marriageDate) {
    freeStr(this->marriageDate);
    copyStr(this->marriageDate, marriageDate);
}

void Spouse::setChildrenList(const char* childrenList) {
    freeStr(this->childrenList);
    copyStr(this->childrenList, childrenList);
}

const char* Spouse::getSpouseName() const {
    return spouseName;
}

const char* Spouse::getMarriageDate() const {
    return marriageDate;
}

const char* Spouse::getChildrenList() const {
    return childrenList;
}

void Spouse::print(std::ostream& os) const {
    Person::print(os);
    os << "Spouse Name: " << spouseName << std::endl;
    os << "Marriage Date: " << marriageDate << std::endl;
    os << "Children List: " << childrenList << std::endl;
}

void Spouse::save(std::ofstream& ofs) const {
    Person::save(ofs);
    ofs << spouseName << std::endl;
    ofs << marriageDate << std::endl;
    ofs << childrenList << std::endl;
}

void Spouse::load(std::ifstream& ifs) {
    Person::load(ifs);
    std::string temp;
    std::getline(ifs, temp);
    setSpouseName(temp.c_str());
    std::getline(ifs, temp);
    setMarriageDate(temp.c_str());
    std::getline(ifs, temp);
    setChildrenList(temp.c_str());
}