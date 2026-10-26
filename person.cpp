#include "person.h"
#include <stdexcept>

void Person::copyStr(char*& dest, const char* src) {
    freeStr(dest);
    if (!src) {
        dest = nullptr;
        return;
    }
    else {
        dest = new char[std::strlen(src)+1];
        std::strcpy(dest, src);
    }
}

void Person::freeStr(char*& str) {
    delete[] str;
    str = nullptr;
}

Person::Person() : name(nullptr), birthDate(nullptr), deathDate(nullptr), age(0) {
    std::cout << "Default constructor called" << std::endl;
    copyStr(name, "Unknown");
    copyStr(birthDate, "Unknown");
    copyStr(deathDate, "Unknown");
}

Person::Person(const char* name, const char* birthDate, const char* deathDate, int age) : name(nullptr), birthDate(nullptr), deathDate(nullptr), age(age) {
    std::cout << "Parameterized constructor called" << std::endl;
    copyStr(this->name, name);
    copyStr(this->birthDate, birthDate);
    copyStr(this->deathDate, deathDate);
    
    if (age < 0) { // Условимся, что у нас в роду есть вампиры и живут они допустим лет по 1000 и более
        throw std::invalid_argument("Age cannot be negative");
    }
}

Person::Person(const Person& other) : Base(other), name(nullptr), birthDate(nullptr), deathDate(nullptr), age(other.age) {
    std::cout << "Copy constructor called" << std::endl;
    copyStr(name, other.name);
    copyStr(birthDate, other.birthDate);
    copyStr(deathDate, other.deathDate);
}

Person& Person::operator=(const Person& other) {
    std::cout << "Assignment operator called" << std::endl;
    if (this != &other) {
        copyStr(name, other.name);
        copyStr(birthDate, other.birthDate);
        copyStr(deathDate, other.deathDate);
        age = other.age;
    }
    return *this;
}

Person::~Person() {
    std::cout << "Destructor called" << std::endl;
    freeStr(name);
    freeStr(birthDate);
    freeStr(deathDate);
}

void Person::print(std::ostream& os) const {
    os << "Name: " << (name ? name : "Unknown") << ", Birth Date: " << (birthDate ? birthDate : "Unknown") 
       << ", Death Date: " << (deathDate ? deathDate : "Unknown") << ", Age: " << age;
}

void Person::save(std::ofstream& ofs) const {
    ofs << (name ? name : "Unknown") << '\n' 
        << (birthDate ? birthDate : "Unknown") << '\n' 
        << (deathDate ? deathDate : "Unknown") << '\n' 
        << age << '\n';
}

void Person::load(std::ifstream& ifs) {
    char buffer[512];
    ifs.getline(buffer, sizeof(buffer));
    copyStr(name, buffer);
    ifs.getline(buffer, sizeof(buffer));
    copyStr(birthDate, buffer);
    ifs.getline(buffer, sizeof(buffer));
    copyStr(deathDate, buffer);
    ifs >> age;
    ifs.ignore(); // Игнорим символ новой строки
}

void Person::setName(const char* name) {
    copyStr(this->name, name);
}

void Person::setBirthDate(const char* birthDate) {
    copyStr(this->birthDate, birthDate);
}

void Person::setDeathDate(const char* deathDate) {
    copyStr(this->deathDate, deathDate);
}

void Person::setAge(int age) {
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative");
    }
    this->age = age;
}

const char* Person::getName() const {
    return name;
}

const char* Person::getBirthDate() const {
    return birthDate;
}

const char* Person::getDeathDate() const {
    return deathDate;
}

int Person::getAge() const {
    return age;
}