// familyMember - класс члена семьи
#pragma once
#include "base.h"

class familyMember : public Base {
    protected:
        char* name;
        char* birthDate;
        char* deathDate;
        int age;

        char* fatherName;
        char* motherName;

        char* spouseName;
        char* marriageDate;

        char* childrenList;

        void copyStr(char*& dest, const char* src);
        void freeStr(char*& str);
    public:
        familyMember();
        familyMember(const char* name, const char* birthDate, const char* deathDate, int age, const char* fatherName, const char* motherName, const char* spouseName, const char* marriageDate, const char* childrenList);
        familyMember(const familyMember& other);
        familyMember& operator=(const familyMember& other);
        virtual ~familyMember();

        // геттеры
        const char* getName() const override {return name;};
        const char* getBirthDate() const {return birthDate;};
        const char* getDeathDate() const {return deathDate;};
        int getAge() const {return age;};
        const char* getFatherName() const {return fatherName;};
        const char* getMotherName() const {return motherName;};
        const char* getSpouseName() const {return spouseName;};
        const char* getMarriageDate() const {return marriageDate;};
        const char* getChildrenList() const {return childrenList;};

        // сеттеры
        void setName(const char* name) {copyStr(this->name, name);};
        void setBirthDate(const char* birthDate) {copyStr(this->birthDate, birthDate);};
        void setDeathDate(const char* deathDate) {copyStr(this->deathDate, deathDate);};
        void setAge(int age) {this->age = age;};
        void setFatherName(const char* fatherName) {copyStr(this->fatherName, fatherName);};
        void setMotherName(const char* motherName) {copyStr(this->motherName, motherName);};
        void setSpouseName(const char* spouseName) {copyStr(this->spouseName, spouseName);};
        void setMarriageDate(const char* marriageDate) {copyStr(this->marriageDate, marriageDate);};
        void setChildrenList(const char* childrenList) {copyStr(this->childrenList, childrenList);};

        Base* clone() const override { return new familyMember(*this); }

        void print(std::ostream& os) const override;
        void save(std::ofstream& ofs) const override;
        void load(std::ifstream& ifs) override;

        bool operator==(const familyMember& other) const;
        bool equals(const Base& other) const override;

};