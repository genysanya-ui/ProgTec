// person - тут данные члена семьи
#pragma once
#include "base.h"

class Person : public Base {
    protected:
        char* name;
        char* birthDate;
        char* deathDate;
        int age;

        void copyStr(char*& dest, const char* src);
        void freeStr(char*& str);

    public:
        Person();
        Person(const char* name, const char* birthDate, const char* deathDate, int age);
        Person(const Person& other);
        Person& operator=(const Person& other);
        virtual ~Person();

        void setName(const char* name);
        void setBirthDate(const char* birthDate);
        void setDeathDate(const char* deathDate);
        void setAge(int age);

        const char* getName() const;
        const char* getBirthDate() const;
        const char* getDeathDate() const;
        int getAge() const;

        void print(std::ostream& os) const override;
        void save(std::ofstream& ofs) const override;
        void load(std::ifstream& ifs) override;

        bool operator==(const Person& other) const { // Сравнение по имени
            return std::strcmp(name, other.name) == 0;
        }

        bool equals(const Base& other) const override { // Сравнение по всем полям
            const Person& otherPerson = dynamic_cast<const Person&>(other);
            return std::strcmp(name, otherPerson.name) == 0 &&
                   std::strcmp(birthDate, otherPerson.birthDate) == 0 &&
                   std::strcmp(deathDate, otherPerson.deathDate) == 0 &&
                   age == otherPerson.age;
        }
    };