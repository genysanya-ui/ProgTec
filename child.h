// Child - класс ребенка
#pragma once
#include "person.h"

class Child : public Person {
    char* fatherName;
    char* motherName;
    char* spouseName;
public:
    Child();
    Child(const char* name, const char* birthDate, const char* deathDate, int age, const char* fatherName, const char* motherName, const char* spouseName);
    Child(const Child& other);
    Child& operator=(const Child& other);
    ~Child() override;

    void setFatherName(const char* fatherName);
    void setMotherName(const char* motherName);
    void setSpouseName(const char* spouseName);
    const char* getFatherName() const;
    const char* getMotherName() const;
    const char* getSpouseName() const;

    Base* clone() const override {
        return new Child(*this);
    }
    const char* getType() const override {
        return "Child";
    }

    void print(std::ostream& os) const override;
    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;
};