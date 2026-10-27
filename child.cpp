#include "child.h"

Child::Child() : Person(), fatherName(nullptr), motherName(nullptr), spouseName(nullptr) {
    std::cout << "Child default constructor called" << std::endl;
    copyStr(fatherName, "Unknown");
    copyStr(motherName, "Unknown");
    copyStr(spouseName, "Unknown");
}

Child::Child(const char* name, const char* birthDate, const char* deathDate, int age, const char* fatherName, const char* motherName, const char* spouseName)
    : Person(name, birthDate, deathDate, age), fatherName(nullptr), motherName(nullptr), spouseName(nullptr) {
    std::cout << "Child parameterized constructor called" << std::endl;
    copyStr(this->fatherName, fatherName);
    copyStr(this->motherName, motherName);
    copyStr(this->spouseName, spouseName);
}

Child::Child(const Child& other) : Person(other), fatherName(nullptr), motherName(nullptr), spouseName(nullptr) {
    std::cout << "Child copy constructor called" << std::endl;
    copyStr(fatherName, other.fatherName);
    copyStr(motherName, other.motherName);
    copyStr(spouseName, other.spouseName);
}

Child& Child::operator=(const Child& other) {
    std::cout << "Child assignment operator called" << std::endl;
    if (this != &other) {
        Person::operator=(other);
        freeStr(fatherName);
        freeStr(motherName);
        freeStr(spouseName);
        copyStr(fatherName, other.fatherName);
        copyStr(motherName, other.motherName);
        copyStr(spouseName, other.spouseName);
    }
    return *this;
}

Child::~Child() {
    std::cout << "Child destructor called" << std::endl;
    freeStr(fatherName);
    freeStr(motherName);
    freeStr(spouseName);
}

void Child::print(std::ostream& os) const {
    Person::print(os);
    os << "Father's Name: " << (fatherName ? fatherName : "Unknown") << std::endl;
    os << "Mother's Name: " << (motherName ? motherName : "Unknown") << std::endl;
    os << "Spouse's Name: " << (spouseName ? spouseName : "Unknown") << std::endl;
}

void Child::save(std::ofstream& ofs) const {
    Person::save(ofs);
    ofs << (fatherName ? fatherName : "Unknown") << std::endl;
    ofs << (motherName ? motherName : "Unknown") << std::endl;
    ofs << (spouseName ? spouseName : "Unknown") << std::endl;
}

void Child::load(std::ifstream& ifs) {
    Person::load(ifs);
    std::string father, mother, spouse;
    std::getline(ifs, father);
    std::getline(ifs, mother);
    std::getline(ifs, spouse);
    setFatherName(father.c_str());
    setMotherName(mother.c_str());
    setSpouseName(spouse.c_str());
}

void Child::setFatherName(const char* fatherName) {
    freeStr(this->fatherName);
    copyStr(this->fatherName, fatherName);
}

void Child::setMotherName(const char* motherName) {
    freeStr(this->motherName);
    copyStr(this->motherName, motherName);
}

void Child::setSpouseName(const char* spouseName) {
    freeStr(this->spouseName);
    copyStr(this->spouseName, spouseName);
}

const char* Child::getFatherName() const {
    return fatherName;
}

const char* Child::getMotherName() const {
    return motherName;
}

const char* Child::getSpouseName() const {
    return spouseName;
}
