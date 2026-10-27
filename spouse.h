// Spouse - класс супруга
#pragma once
#include "person.h"

class Spouse : public Person {
    char* spouseName;
    char* marriageDate;
    char* childrenList; // Список детей через ';'
public:
    Spouse();
    Spouse(const char* name, const char* birthDate, const char* deathDate, int age, const char* spouseName, const char* marriageDate, const char* childrenList);
    Spouse(const Spouse& other);
    Spouse& operator=(const Spouse& other);
    ~Spouse() override;

    void setSpouseName(const char* spouseName);
    void setMarriageDate(const char* marriageDate);
    void setChildrenList(const char* childrenList);
    const char* getSpouseName() const;
    const char* getMarriageDate() const;
    const char* getChildrenList() const;

    Base* clone() const override {
        return new Spouse(*this);
    }
    const char* getType() const override {
        return "Spouse";
    }
    void print(std::ostream& os) const override;
    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;
};