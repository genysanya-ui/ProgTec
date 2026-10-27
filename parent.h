// Parent - класс родителя
#include "person.h"

class Parent : public Person {
    char* fatherName;
    char* motherName;
    char* childrenList; // Список детей через ';'
    
    public:
        Parent();
        Parent(const char* name, const char* birthDate, const char* deathDate, int age, const char* fatherName, const char* motherName, const char* childrenList);
        Parent(const Parent& other);
        Parent& operator=(const Parent& other);
        ~Parent() override;

        void setFatherName(const char* fatherName);
        void setMotherName(const char* motherName);
        void setChildrenList(const char* childrenList);
        const char* getFatherName() const;
        const char* getMotherName() const;
        const char* getChildrenList() const;

        Base* clone() const override {
            return new Parent(*this);
        }
        const char* getType() const override {
            return "Parent";
        }
        void print(std::ostream& os) const override;
        void save(std::ofstream& ofs) const override;
        void load(std::ifstream& ifs) override;

};