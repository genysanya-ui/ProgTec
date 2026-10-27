#include "parent.h"

Parent::Parent() : Person(), fatherName(nullptr), motherName(nullptr), childrenList(nullptr) {
    std::cout << "Parent default constructor called" << std::endl;
    copyStr(fatherName, "Unknown");
    copyStr(motherName, "Unknown");
    copyStr(childrenList, "None");
}

Parent::Parent(const char* name, const char* birthDate, const char* deathDate, int age, const char* fatherName, const char* motherName, const char* childrenList)
    : Person(name, birthDate, deathDate, age), fatherName(nullptr), motherName(nullptr), childrenList(nullptr) {
    std::cout << "Parent parameterized constructor called" << std::endl;
    copyStr(this->fatherName, fatherName);
    copyStr(this->motherName, motherName);
    copyStr(this->childrenList, childrenList);
}

Parent::Parent(const Parent& other) : Person(other), fatherName(nullptr), motherName(nullptr), childrenList(nullptr) {
    std::cout << "Parent copy constructor called" << std::endl;
    copyStr(fatherName, other.fatherName);
    copyStr(motherName, other.motherName);
    copyStr(childrenList, other.childrenList);
}

Parent& Parent::operator=(const Parent& other) {
    std::cout << "Parent assignment operator called" << std::endl;
    if (this != &other) {
        Person::operator=(other);
        copyStr(fatherName, other.fatherName);
        copyStr(motherName, other.motherName);
        copyStr(childrenList, other.childrenList);
    }
    return *this;
}

Parent::~Parent() {
    std::cout << "Parent destructor called" << std::endl;
    freeStr(fatherName);
    freeStr(motherName);
    freeStr(childrenList);
}

void Parent::setFatherName(const char* fatherName) {
    copyStr(this->fatherName, fatherName);
}

void Parent::setMotherName(const char* motherName) {
    copyStr(this->motherName, motherName);
}

void Parent::setChildrenList(const char* childrenList) {
    copyStr(this->childrenList, childrenList);
}

const char* Parent::getFatherName() const {
    return fatherName;
}

const char* Parent::getMotherName() const {
    return motherName;
}

const char* Parent::getChildrenList() const {
    return childrenList;
}

void Parent::print(std::ostream& os) const {
    Person::print(os);
    os << "Father's Name: " << fatherName << "\n";
    os << "Mother's Name: " << motherName << "\n";
    os << "Children List: " << childrenList << "\n";
}

void Parent::save(std::ofstream& ofs) const {
    Person::save(ofs);
    ofs << (fatherName ? fatherName : "Unknown") << '\n'
        << (motherName ? motherName : "Unknown") << '\n'
        << (childrenList ? childrenList : "None") << '\n';
}

void Parent::load(std::ifstream& ifs) {
    Person::load(ifs);
    char buffer[512];
    ifs.getline(buffer, sizeof(buffer));
    copyStr(fatherName, buffer);
    ifs.getline(buffer, sizeof(buffer));
    copyStr(motherName, buffer);
    ifs.getline(buffer, sizeof(buffer));
    copyStr(childrenList, buffer);
}